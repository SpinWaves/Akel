// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/02/2023
// Updated : 10/02/2023

#include <Renderer/Images/cubemap.h>
#include <Core/log.h>

namespace Ak
{
	CubeMap::CubeMap(std::filesystem::path cube_map_file) : _file(cube_map_file)
	{
		if(!std::filesystem::exists(_file))
			Core::log::report(FATAL_ERROR, "Cube Map : cube map file doesn't exists'");
		load();
	}

	CubeMap::CubeMap(CubeMapParts parts, std::string name)
	{
		_file = parts.top.remove_filename() / name / ".akcub";
		load();
	}

	void CubeMap::load() noexcept
	{

	}
}
