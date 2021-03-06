-- This file is a part of Akel
-- Author : @kbz_8
-- Created : 02/10/2021
-- Updated : 05/07/2022

-- Globals settings
add_repositories("local-repo libs")

add_requires("libsdl_image", "libsdl", "libsdl_ttf", "libsndfile", "openal-soft", "spirv-reflect", "vulkan-loader", "imgui_sdl_vk v1.87-docking", "imguizmo_shared")

add_rules("mode.debug", "mode.release")
set_languages("cxx17")

set_objectdir("build-int/$(os)_$(arch)")
set_targetdir("build/$(os)_$(arch)")

-- Lib Akel Build
target("Akel")
	set_default(true)
	set_kind("shared")
	add_files("Akel/src/**.cpp")
	add_includedirs("Akel/src", "libs/include")

	if is_mode("debug") then
		add_defines("AK_DEBUG")
	elseif is_mode("release") then
		add_defines("AK_RELEASE")
	end

	add_defines("MAIN_PATH=\"$(projectdir)/\"")

	set_pcxxheader("Akel/src/Akpch.h")
	
	add_defines("SDL_MAIN_HANDLED")

	add_packages("libsdl_image",  { public = true })
	add_packages("libsdl",		  { public = true })
	add_packages("libsdl_ttf",    { public = true })
	add_packages("libsndfile",    { public = true })
	add_packages("openal-soft",   { public = true })
	add_packages("vulkan-loader", { public = true })
	add_packages("spirv-reflect", { public = true })
	add_packages("imgui_sdl_vk",  { public = true })

	on_load(function(target)
		os.cp("$(projectdir)/libs/packages/i/imgui_sdl_vk/install/libimgui_sdl_vk.so", "build/$(os)_$(arch)/")
    end);
target_end() -- optional but I think the code is cleaner with this

-- Akel Studio Build
target("Akel_Studio")
	set_default(true)
    set_kind("binary")
	add_includedirs("Akel/src", "Akel_Studio/src", "libs/include")
    add_deps("Akel")
    add_files("Akel_Studio/src/**.cpp")

	add_packages("imguizmo_shared")

	set_pcxxheader("Akel_Studio/src/AkSpch.h")

	if is_mode("debug") then
		add_defines("AK_STUDIO_DEBUG")
	elseif is_mode("release") then
		add_defines("AK_STUDIO_RELEASE")
	end
target_end()

-- Rectangle Demo Build
target("RectDemo")
	set_default(false)
    set_kind("binary")
    add_deps("Akel")
	add_includedirs("Akel/src", "SandBox/rect/src", "libs/include")
    add_files("SandBox/rect/src/*.cpp")
target_end()

-- Cube Demo Build
target("CubeDemo")
	set_default(false)
    set_kind("binary")
    add_deps("Akel")
	add_includedirs("Akel/src", "SandBox/cube/src", "libs/include")
    add_files("SandBox/cube/src/*.cpp")
target_end()

-- Kila tester Build
target("Kila_tester")
	set_default(false)
    set_kind("binary")
    add_deps("Akel")
	add_includedirs("Akel/src", "Tests/Kila", "libs/include")
    add_files("Tests/Kila/*.cpp")
target_end()
