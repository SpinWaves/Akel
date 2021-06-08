project "Editor"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	architecture "x86_64"
	icon "../Akel/src/assets/logo.png"

	targetdir ("../build/" .. outputdir)
	objdir ("../build-int/" .. outputdir)

	pchheader "src/AkEpch.h"
	pchsource "src/AkEpch.cpp"
	flags "NoPCH"

	filter {"system:windows", "configurations:Release"}
		libdirs {"../libs/lib/Windows", "../build/Release-windows"}
	filter {"system:windows", "configurations:Debug"}
		libdirs {"../libs/lib/Windows", "../build/Debug-windows"}

	filter {"system:linux", "configurations:Release"}
		libdirs {"../libs/lib/Linux", "../build/Release-linux"}
	filter {"system:linux", "configurations:Debug"}
		libdirs {"../libs/lib/Linux", "../build/Debug-linux"}

	links
	{
		"ImGui",
		"Akel"
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
		"../libs/include"
	}


	filter "configurations:Debug"
        defines "AK_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "AK_RELEASE"
        optimize "On"

