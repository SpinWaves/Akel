// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2023
// Updated : 11/02/2023

namespace Ak
{
	template <shaderlang lang>
	void Scene::loadCustomShader(std::filesystem::path path)
	{
		if(lang == shaderlang::spirv)
			_shaders.push_back(load_spirv_from_file(path.c_str()));
		else
			_loadCustomShader(lang, std::move(path));
	}
}
