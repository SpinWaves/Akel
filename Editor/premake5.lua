project "Editor"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	architecture "x86_64"
	icon "../Ressources/logo.ico"

	targetdir ("../build/" .. outputdir)
	objdir ("../build-int/" .. outputdir)

	pchheader "src/AkEpch.h"
	pchsource "src/AkEpch.cpp"
	flags "NoPCH"

	filter "system:windows"
		libdirs "../libs/lib/Windows"
	filter "system:linux"
		libdirs "../libs/lib/Linux"

	links
	{
		"Akel",
		"ImGui"
	}

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"../Akel/src",
		"src",
		"../libs/include",
		"../dependencies"
	}


	filter "configurations:Debug"
        defines "AK_EDITOR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "AK_EDITOR_RELEASE"
        optimize "On"
