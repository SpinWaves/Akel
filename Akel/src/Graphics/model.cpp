// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2023
// Updated : 12/02/2023

#include <Graphics/model.h>

namespace Ak
{
	Model(std::filesystem::path file) : _file(std::move(file))
	{

	}

	Model(const Mesh& mesh)
	{
		_meshes.push_back(mesh);
	}

	Model(Mesh&& mesh)
	{
		_meshes.push_back(std::move(mesh));
	}
}
