set_xmakever("2.5.6")

add_requires("libsdl_image")
add_requires("libsdl")
add_requires("libsdl_ttf")
add_requires("libsndfile")
add_requires("openal-soft")
add_requires("vulkan-headers")

add_rules("mode.debug", "mode.release")
set_languages("cxx17")

set_objectdir("../../build-int/$(os)_$(arch)_$(mode)")
set_targetdir("../../build/$(os)_$(arch)_$(mode)")

target("Akel")
	set_kind("shared")
	add_files("../../Akel/src/**.cpp")
	add_includedirs("../../Akel/src", "../../libs/include")

	if is_mode("debug") then
		add_defines("AK_DEBUG")
	elseif is_mode("release") then
		add_defines("AK_RELEASE")
	end

	set_pcxxheader("../../Akel/src/Akpch.h")

	add_defines("SDL_MAIN_HANDLED")

	add_packages("libsdl_image")
	add_packages("libsdl")
	add_packages("libsdl_ttf")
	add_packages("libsndfile")
	add_packages("openal-soft", { configs = { shared = true }})
	add_packages("vulkan-headers")

target("Rect")
    set_kind("binary")
    add_deps("Akel")
	add_includedirs("../../Akel/src", "src", "../../libs/include")
    add_files("src/**.cpp")
