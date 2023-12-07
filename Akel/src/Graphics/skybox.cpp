// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/11/2023
// Updated : 01/11/2023

#include <Graphics/skybox.h>

namespace Ak
{
	Skybox::Skybox(const SkyboxDesc& description)
	{
	}

	Skybox::Skybox(const std::filesystem::path& file)
	{
		_cubemap = CubemapLibrary::get().addCubemapToLibrary(file);
	}
}
