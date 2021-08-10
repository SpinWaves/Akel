workspace "Akel"
	startproject "ImGui"
	startproject "Akel"
	startproject "Editor"

	configurations
	{
		"Debug",
		"Release"
	}

	outputdir = "%{cfg.system}"

include "dependencies/imgui"
include "Akel"
include "Editor"
