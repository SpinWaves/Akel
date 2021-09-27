workspace "Akel Cube"
	startproject "Akel"
    startproject "Cube"

	configurations
	{
		"Debug",
		"Release"
	}

	outputdir = "%{cfg.system}"

include "../../Akel"

project "Cube"
    kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	architecture "x86_64"
	buildoptions "-O3"
	icon "../../Ressources/logo.ico"

	targetdir ("build/" .. outputdir)
	objdir ("build-int/" .. outputdir)

	filter "system:windows"
		libdirs "../../libs/lib/Windows"
	filter "system:linux"
		libdirs "../../libs/lib/Linux"

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
		"../../Akel/src",
		"src",
		"../../libs/include",
		"../../dependencies"
	}
