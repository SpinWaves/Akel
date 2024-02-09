-- This file is a part of Akel
-- Authors : @kbz_8
-- Created : 02/10/2021
-- Updated : 03/01/2024

-- Credits to SirLynix (https://github.com/SirLynix) for this xmake.lua
-- Took from https://github.com/NazaraEngine/NazaraEngine

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
	set_fpmodels("fast")
	add_vectorexts("sse", "sse2", "sse3", "ssse3")
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

local system_interfaces = {
	SDL2 = {
		option = "SDL2_backend",
		dir = "Drivers/",
		default = true,
		publicPackages = {"libsdl"},
		custom = function()
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
	},
	GLFW = {
		option = "GLFW_backend",
		dir = "Drivers/",
		default = false,
		publicPackages = {"glfw"},
		custom = function()
			add_defines("GLFW_INCLUDE_NONE")
			if is_plat("linux") then
				add_packages("libxext", "wayland", { links = {} }) -- we only need X11 headers
			elseif is_plat("macosx") then
				add_packages("libx11", { links = {} }) -- we only need X11 headers
			end
		end
	}
}

local os_interfaces = {
	Unix = {
		dir = "Drivers/",
		enabled = is_plat("linux")
	},
	MacOS = {
		dir = "Drivers/",
		enabled = is_plat("macosx"),
		custom = function()
			add_files("Akel/Runtime/Sources/Drivers/MacOS/**.mm")
		end
	},
	Windows = {
		dir = "Drivers/",
		enabled = is_plat("windows")
	}
	-- TODO : wasm
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
		deps = {"AkelUtils"},
		custom = function()
			add_headerfiles("Akel/Runtime/Includes/Maths/**.h", "Akel/Runtime/Includes/Maths/**.inl")
			for name, module in table.orderpairs(os_interfaces) do
				if module.enabled then
					ModuleTargetConfig(name, module)
				end
			end
		end
	},
	Graphics = {
		deps = {"AkelRenderer", "AkelCore"},
		packages = {"entt"}
	},
	Platform = {
		option = "platform",
		deps = {"AkelUtils", "AkelCore"},
		custom = function()
			for name, module in table.orderpairs(system_interfaces) do
				if has_config(module.option) then
					ModuleTargetConfig(name, module)
				end
			end
		end
	},
	Renderer = {
		option = "renderer",
		deps = {"AkelPlatform", "AkelCore"},
		packages = {},
		publicPackages = {"nzsl"},
		custom = function()
			if has_config("embed_rendererbackends", "static") then
				for name, module in table.orderpairs(renderer_backends) do
					if not module.option or has_config(module.option) then
						ModuleTargetConfig(name, module)
					end
				end
			end
		end
	},
	Utils = {
		deps = {}
	},
	ELTM = {
		option = "eltm",
		deps = {"AkelUtils"},
		dir = "Plugins/"
	}
}

local sanitizers = {
	asan = "address",
	lsan = "leak",
	tsan = "thread",
}

for opt, policy in table.orderpairs(sanitizers) do
	option(opt, { description = "Enable " .. opt, default = false })

	if has_config(opt) then
		set_policy("build.sanitizer." .. policy, true)
	end
end

if is_plat("wasm") then
	renderer_backends.Vulkan = nil
	system_interfaces.GLFW = nil
end

if not has_config("embed_rendererbackends", "static") then
	-- Register renderer backends as separate modules
	for name, module in pairs(renderer_backends) do
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

for name, module in table.orderpairs(system_interfaces) do
	if module.option then
		option(module.option, { description = "Enables the " .. name .. " backend", default = module.default, category = "Modules" })
	end
end

add_rules("build.rendererplugins")

option("static", { description = "Build the engine statically (implies embed_rendererbackends)", default = is_plat("wasm") or false })
option("embed_rendererbackends", { description = "Embed renderer backend code into AkelRenderer instead of loading them dynamically", default = is_plat("wasm") or false })

add_requires("entt")

if has_config("renderer") then
	add_requires("nzsl >=2023.12.31", { debug = is_mode("debug"), configs = { symbols = not is_mode("release"), shared = not is_plat("wasm", "android") and not has_config("static") } })
end

if has_config("SDL2_backend") then
	add_requires("libsdl >=2.26.0")
	add_defines("AK_USE_SDL2")
end

if has_config("GLFW_backend") then
	add_requires("glfw")
	add_defines("AK_USE_GLFW")
end

if is_plat("linux") then
	add_requires("libxext", "wayland", { configs = { asan = false } })
end

if has_config("vulkan") and not is_plat("wasm") then
	add_requires("vulkan-headers", "vulkan-memory-allocator", "volk")
end

function ModuleTargetConfig(name, module)
	add_defines("AK_" .. name:upper() .. "_BUILD")
	if is_mode("debug") then
		add_defines("AK_" .. name:upper() .. "_DEBUG")
	end

	if is_plat("wasm") or has_config("static") then
		add_defines("AK_".. name:upper() .. "_STATIC", { public = true })
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

	if module.packages then
		add_packages(table.unpack(module.packages))
	end

	if module.publicPackages then
		for _, pkg in ipairs(module.publicPackages) do
			add_packages(pkg, { public = true })
		end
	end

	if module.deps then
		local moduleName = "Akel" .. name
		table.remove_if(module.deps, function(dep)
			return module.deps[dep] == moduleName
		end)
		if #module.deps > 0 then
			add_deps(table.unpack(module.deps))
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

	target("Akel" .. name, function()
		set_group("Modules")

		-- handle shared/static kind
		if is_plat("wasm") or has_config("static") then
			set_kind("static")
		else
			set_kind("shared")
		end

		add_includedirs("Akel/Runtime/Sources")
		add_rpathdirs("$ORIGIN")

		if module.dir then
			set_pcxxheader("Akel/Runtime/Includes/" .. module.dir .. name .. "/PreCompiled.h")
		else
			set_pcxxheader("Akel/Runtime/Includes/" .. name .. "/PreCompiled.h")
		end

		on_clean(function(target)
			if target:objectfiles() then
				for _, file in ipairs(target:objectfiles()) do
					if os.exists(file) then
						print("Removing " .. file)
						os.rm(file)
					end
				end
			end
			if target:targetfile() and os.exists(target:targetfile()) then
				print("Removing " .. target:targetfile())
				os.rm(target:targetfile())
			end
		end)

		ModuleTargetConfig(name, module)
	end)

	::continue::
end

rule("build.rendererplugins")
	on_load(function(target)
		if has_config("static") then
			return
		end

		local deps = table.wrap(target:get("deps"))

		if target:kind() == "binary" and (table.contains(deps, "AkelRenderer") or table.contains(deps, "AkelGraphics")) then
			for name, _ in pairs(renderer_backends) do
				local depName = "Akel" .. name
				if not table.contains(deps, depName) then -- don't overwrite dependency
					target:add("deps", depName, {inherit = false})
				end
			end
		end
	end)

includes("SandBox/Native/*.lua")
