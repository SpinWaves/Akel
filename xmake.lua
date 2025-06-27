-- Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
-- This file is a part of Akel
-- For conditions of distribution and use, see copyright notice in LICENSE

-- Credits to SirLynix (https://github.com/SirLynix) for this xmake.lua
-- Took from https://github.com/NazaraEngine/NazaraEngine

-- add_requireconfs("imgui", { configs = { cxflags = "-D IMGUI_IMPL_VULKAN_NO_PROTOTYPES" }})

set_version("0.0.1beta")

set_languages("cxx23")

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

set_configdir("Akel/BuildTime/")
add_configfiles("Akel/BuildTime/Config.h.in")

local renderer_backends = {
	Vulkan = {
		option = "vulkan",
		deps = {"AkelGraphics"},
		packages = {"vulkan-headers", "vulkan-memory-allocator"},
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
	},
	WebGPU = {
		option = "webgpu",
		deps = {"AkelGraphics"},
		packages = {"wgpu-native"},
		dir = "Drivers/"
	}
}

local system_interfaces = {
	SDL2 = {
		option = "SDL2_backend",
		dir = "Drivers/",
		default = true,
		packages = {"libsdl2"},
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
		packages = {"glfw"},
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
		publicPackages = {"toml++"},
		deps = {},
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
		option = "graphics",
		deps = {"AkelCore", "AkelPlatform"},
		publicPackages = {"nzsl"},
		packages = {"entt"},
		custom = function()
			if has_config("embed_rendererbackends", "static") then
				add_defines("AK_EMBEDDED_RENDERER_DRIVERS")
				for name, module in table.orderpairs(rendererBackends) do
					if not module.Option or has_config(module.Option) then
						if module.Deps then
							module = table.clone(module, 1) -- shallow clone
							if #module.Deps == 0 then 
								module.Deps = nil 
							end
						end

						ModuleTargetConfig(name, module)
					end
				end
			end
		end
	},
	Platform = {
		option = "platform",
		deps = {"AkelCore"},
		custom = function()
			for name, module in table.orderpairs(system_interfaces) do
				if has_config(module.option) then
					ModuleTargetConfig(name, module)
				end
			end
		end
	},
	ELTM = {
		option = "eltm",
		deps = {},
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
option("unitybuild", { description = "Build the engine using unity build", default = false })

add_requires("entt", "toml++")

if has_config("graphics") then
	add_requires("nzsl", { debug = is_mode("debug"), configs = { symbols = not is_mode("release"), shared = not is_plat("wasm", "android") and not has_config("static") } })
end

if has_config("SDL2_backend") then
	add_requires("libsdl2 >=2.26.0")
	add_defines("AK_SDL2_DRIVER")
end

if has_config("GLFW_backend") then
	add_requires("glfw")
	add_defines("AK_GLFW_DRIVER")
end

if is_plat("linux") then
	add_requires("libxext", "wayland", { configs = { asan = false } })
end

if has_config("vulkan") and not is_plat("wasm") then
	add_requires("vulkan-headers", "vulkan-memory-allocator")
end

if has_config("webgpu") then
	add_requires("wgpu-native")
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

	if module.dir then
		set_pcxxheader("Akel/Runtime/Includes/" .. module.dir .. name .. "/PreCompiled.h")
	else
		set_pcxxheader("Akel/Runtime/Includes/" .. name .. "/PreCompiled.h")
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
		add_deps(table.unpack(module.deps))
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
		add_includedirs("Akel/BuildTime")
		add_rpathdirs("$ORIGIN")

		if has_config("unitybuild") then
			add_rules("c++.unity_build", { batchsize = 6 })
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

		if target:kind() == "binary" and table.contains(deps, "AkelGraphics") then
			for name, module in pairs(renderer_backends) do
				if has_config(module.option) then
					local depName = "Akel" .. name
					if not table.contains(deps, depName) then -- don't overwrite dependency
						target:add("deps", depName, {inherit = false})
					end
				end
			end
		end
	end)

includes("SandBox/Native/*.lua")
