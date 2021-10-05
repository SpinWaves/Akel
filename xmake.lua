set_xmakever("2.5.6")

add_repositories("local-repo libs")

add_requires("libsdl_image")
add_requires("libsdl")
add_requires("libsdl_ttf")
add_requires("libsndfile")
add_requires("openal-soft")
add_requires("vulkan-headers")
add_requires("vulkan-loader")
add_requires("vulkan-tools")
add_requires("imgui_sdl_vk")

add_rules("mode.debug", "mode.release")
set_languages("cxx17")

set_objectdir("build-int/$(os)_$(arch)")
set_targetdir("build/$(os)_$(arch)")

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

	set_pcxxheader("Akel/src/Akpch.h")

	add_defines("SDL_MAIN_HANDLED")

	add_packages("libsdl_image")
	add_packages("libsdl")
	add_packages("libsdl_ttf")
	add_packages("libsndfile")
	add_packages("openal-soft")
	add_packages("imgui_sdl_vk")
	add_packages("vulkan-headers")
	add_packages("vulkan-loader")
	add_packages("vulkan-tools")
target_end() -- optional but I think the code is cleaner with this

target("Editor")
	set_default(true)
    set_kind("binary")
	add_includedirs("Akel/src", "Editor/src", "libs/include")
    add_deps("Akel")
    add_files("Editor/src/**.cpp")

	add_packages("imgui_sdl_vk")
	set_pcxxheader("Editor/src/AkEpch.h")

	if is_mode("debug") then
		add_defines("AK_EDITOR_DEBUG")
	elseif is_mode("release") then
		add_defines("AK_EDITOR_RELEASE")
	end
target_end() -- optional but I think the code is cleaner with this

target("RectDemo")
	set_default(false)
    set_kind("binary")
    add_deps("Akel")
	add_includedirs("Akel/src", "SandBox/rect/src", "libs/include")
    add_files("SandBox/rect/src/*.cpp")
target_end() -- optional but I think the code is cleaner with this
