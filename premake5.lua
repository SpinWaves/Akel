project "AtlasEngine"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	architecture "x86_64"

	targetdir ("%{prj.location}/build/" .. outputdir)
	objdir ("%{prj.location}/build-int/" .. outputdir)

	pchheader "src/AEpch.h"
	pchsource "src/AEpch.cpp"
	flags "NoPCH"
	linkoptions "-shared"

	filter "system:windows"
		libdirs "libs/lib/Windows"

	filter "system:linux"
		libdirs "libs/lib/Linux"

	links
	{
		"vulkan",
		"SDL2",
		"SDL2_image",
		"SDL2_mixer",
		"SDL2_ttf"
	}

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines "SDL_MAIN_HANDLED"

	includedirs 
	{
		"%{prj.location}/libs/include",
		"%{prj.location}/src"
	}


	filter "configurations:Debug"
        defines "AE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "AE_RELEASE"
        optimize "On"
