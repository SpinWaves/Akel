workspace "Akel"
	startproject "Akel"
	startproject "Editor"

	configurations
	{
		"Debug",
		"Release"
	}

	flags "MultiProcessorCompile"
	outputdir = "%{cfg.buildcfg}-%{cfg.system}"

include "Akel"
include "Editor"	
