project "AtlasEngine"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{prj.location}/build/" .. outputdir)
	objdir ("%{prj.location}/build-int/" .. outputdir)

	pchheader "src/AEpch.h"
	pchsource "src/AEpch.cpp"
	flags "NoPCH"
	linkoptions "-shared"
	
--[[
	platforms {
        "Win32",
        "Win64",
        "macos",
        "linux86",
        "linux86_64",
        -- etc.
    }
	filter {"platforms:Win32"}
		system "Windows"
		architecture "x86"
		libdirs "./libs/lib/Windows/mingw/x86_64"

	filter {"platforms:Win64"}
		system "Windows"
		architecture "x86_64"
		libdirs "./libs/lib/Windows/mingw/x86_64"

	filter {"platforms:linux86"}
		system "linux"
		architecture "x86"
		libdirs "./libs/lib/Linux/x86_64"

	filter {"platforms:linux86_64"}
		system "linux"
		architecture "x86_64"
		libdirs "./libs/lib/Linux/x86_64"
	
	filter {"platforms:macos"}
		system "macosx"
--]]

	libdirs "%{prj.location}/libs/lib/Linux/x86_64"
	
	links
	{
		"GLEW",
		"GL",
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

	defines {"GLEW_STATIC", "SDL_MAIN_HANDLED"}

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
