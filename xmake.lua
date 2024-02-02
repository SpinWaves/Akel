-- This file is a part of Akel
-- Authors : @kbz_8
-- Created : 02/10/2021
-- Updated : 08/07/2023

-- Globals settings
add_repositories("nazara-engine-repo https://github.com/NazaraEngine/xmake-repo")

-- add_requireconfs("imgui", { configs = { cxflags = "-D IMGUI_IMPL_VULKAN_NO_PROTOTYPES" }})

set_languages("cxx17")

add_rules("mode.debug", "mode.release")
set_allowedplats("windows", "mingw", "linux", "macosx", "wasm")
set_allowedmodes("debug", "release")
set_defaultmode("release")

set_project("AkelEngine")

if is_mode("debug") then
	add_defines("AK_DEBUG")
elseif is_mode("release") then
	add_defines("AK_RELEASE")
end

add_includedirs("Akel/Runtime/Includes")
add_sysincludedirs("Akel/ThirdParty")

set_objectdir("build/Objs/$(os)_$(arch)")
set_targetdir("build/Bin/$(os)_$(arch)")
set_rundir("build/Bin/$(os)_$(arch)")
set_dependir("build/.deps")

set_optimize("fastest")

local renderer_backends = {
	Vulkan = {
		option = "vulkan",
		deps = {"AkelRenderer"},
		packages = {"vulkan-headers", "vulkan-memory-allocator", "volk"},
		dir = "Drivers/",
		custom = function()
			add_defines("VK_NO_PROTOTYPES")
			if is_plat("windows", "mingw") then
				add_defines("VK_USE_PLATFORM_WIN32_KHR")
			elseif is_plat("linux") then
				add_defines("VK_USE_PLATFORM_XLIB_KHR")
				add_defines("VK_USE_PLATFORM_WAYLAND_KHR")
				add_packages("libxext", "wayland", { links = {} }) -- we only need X11 headers
			elseif is_plat("macosx") then
				add_defines("VK_USE_PLATFORM_METAL_EXT")
			end
		end
	}
}

local user_interfaces = {
	SDL2 = {
		option = "sdl2",
		deps = {"AkelPlatform"},
		packages = {"libsdl >=2.26.0"},
		dir = "Drivers/",
		custom = function()
			add_packages("libsdl")
			if is_plat("windows", "mingw") then
				add_defines("SDL_VIDEO_DRIVER_WINDOWS=1")
			elseif is_plat("linux") then
				add_defines("SDL_VIDEO_DRIVER_X11=1")
				add_defines("SDL_VIDEO_DRIVER_WAYLAND=1")
				add_packages("libxext", "wayland", { links = {} }) -- we only need X11 headers
			elseif is_plat("macosx") then
				add_defines("SDL_VIDEO_DRIVER_COCOA=1")
				add_packages("libx11", { links = {} }) -- we only need X11 headers
			elseif is_plat("wasm") then
				-- emscripten enables USE_SDL by default which will conflict with the sdl headers
				add_cxflags("-sUSE_SDL=0")
				add_ldflags("-sUSE_SDL=0", { public = true })
			end
		end
	}
}

local modules = {
	Audio = {
		option = "audio",
		deps = {"AkelCore"},
		custom = function()
			if is_plat("wasm") then
				add_syslinks("openal")
			else
				add_packages("openal-soft", { links = {} })
			end
		end
	},
	Core = {
		custom = function ()
			add_headerfiles("Akel/Runtime/Includes/Maths/**.h", "Akel/Runtime/Includes/Maths/**.inl")
		end
	},
	Graphics = {
		deps = {"AkelRenderer", "AkelCore"},
		packages = {"entt"}
	},
	Platform = {
		option = "platform",
		deps = {"AkelUtils", "AkelCore"}
	},
	Renderer = {
		option = "renderer",
		deps = {"AkelPlatform", "AkelCore"},
		packages = {},
		publicPackages = {"nzsl"},
		custom = function ()
			if has_config("static") then
				for name, module in table.orderpairs(renderer_backends) do
					if not module.Option or has_config(module.Option) then
						ModuleTargetConfig(name, module)
					end
				end
			end
		end
	},
	Utils = {
		option = "utils",
		deps = {"AkelCore"}
	},
	ELTM = {
		option = "eltm",
		deps = {"AkelUtils"},
		dir = "Plugins/"
	}
}

if is_plat("wasm") then
	renderer_backends.Vulkan = nil
end

if not has_config("static") then
	-- Register renderer backends as separate modules
	for name, module in pairs(renderer_backends) do
		if (modules[name] ~= nil) then
			os.raise("overriding module " .. name)
		end

		modules[name] = module
	end
end

if not has_config("static") then
	-- Register user interfaces backends as separate modules
	for name, module in pairs(user_interfaces) do
		if (modules[name] ~= nil) then
			os.raise("overriding module " .. name)
		end

		modules[name] = module
	end
end

for name, module in table.orderpairs(modules) do
	if module.option then
		option(module.option, { description = "Enables the " .. name .. " module", default = true, category = "Modules" })
	end
end

add_requires("entt")

if has_config("renderer") then
	add_requires("nzsl >=2023.12.31", { debug = is_mode("debug"), configs = { symbols = not is_mode("release"), shared = not is_plat("wasm", "android") and not has_config("static") } })
end

if has_config("sdl2") then
	add_requires("libsdl >=2.26.0")
end

if is_plat("linux") then
	add_requires("libxext", "wayland", { configs = { asan = false } })
end

if has_config("vulkan") and not is_plat("wasm") then
	add_requires("vulkan-headers", "vulkan-memory-allocator", "volk")
end

if is_plat("linux") then
	add_requires("libxext", "wayland", { configs = { asan = false } })
end

function ModuleTargetConfig(name, module)
	add_defines("AK_" .. name:upper() .. "_BUILD")
	if is_mode("debug") then
		add_defines("AK_" .. name:upper() .. "_DEBUG")
	end

	-- Add header and source files
	for _, ext in ipairs({".h", ".hpp", ".inl"}) do
		if module.dir then
			add_headerfiles("Akel/Runtime/Includes/" .. module.dir .. name .. "/**" .. ext)
			add_headerfiles("Akel/Runtime/Sources/" .. module.dir .. name .. "/**" .. ext, { prefixdir = "private", install = false })
		else
			add_headerfiles("Akel/Runtime/Includes/" .. name .. "/**" .. ext)
			add_headerfiles("Akel/Runtime/Sources/" .. name .. "/**" .. ext, { prefixdir = "private", install = false })
		end
	end

	if module.dir then
		remove_headerfiles("Akel/Runtime/Sources/" .. module.dir .. name .. "/Resources/**.h")
	else
		remove_headerfiles("Akel/Runtime/Sources/" .. name .. "/Resources/**.h")
	end

	-- Add extra files for projects
	for _, ext in ipairs({".nzsl"}) do
		if module.dir then
			add_extrafiles("Akel/Runtime/Includes/" .. module.dir .. name .. "/**" .. ext)
			add_extrafiles("Akel/Runtime/Sources" .. module.dir .. name .. "/**" .. ext)
		else
			add_extrafiles("Akel/Runtime/Includes/" .. name .. "/**" .. ext)
			add_extrafiles("Akel/Runtime/Sources" .. name .. "/**" .. ext)
		end
	end

	if module.dir then
		add_files("Akel/Runtime/Sources/" .. module.dir .. name .. "/**.cpp")
	else
		add_files("Akel/Runtime/Sources/" .. name .. "/**.cpp")
	end

	if module.custom then
		module.custom()
	end
end

for name, module in pairs(modules) do
	if module.option and not has_config(module.option) then
		goto continue
	end

	target("Akel" .. name, function ()
		set_group("Modules")

		-- handle shared/static kind
		if is_plat("wasm") or has_config("static") then
			set_kind("static")
			add_defines("AK_".. name:upper() .. "_STATIC", { public = true })
		else
			set_kind("shared")
		end

		add_includedirs("Akel/Runtime/Sources")
		add_rpathdirs("$ORIGIN")

		if module.deps then
			add_deps(table.unpack(module.deps))
		end

		if module.packages then
			add_packages(table.unpack(module.packages))
		end

		if module.publicPackages then
			for _, pkg in ipairs(module.publicPackages) do
				add_packages(pkg, { public = true })
			end
		end

		if module.dir then
			set_pcxxheader("Akel/Runtime/Includes/" .. module.dir .. name .. "/PreCompiled.h")
		else
			set_pcxxheader("Akel/Runtime/Includes/" .. name .. "/PreCompiled.h")
		end

		on_clean(function(target)
			os.rm(target:targetfile())
		end)

		ModuleTargetConfig(name, module)
	end)

	::continue::
end
