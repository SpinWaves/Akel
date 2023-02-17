// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/02/2023
// Updated : 17/02/2023

#include <Core/log.h>
#include <Renderer/Pipeline/shaders_library.h>

namespace Ak
{
	std::shared_ptr<Shader> ShadersLibrary::getShader(ShaderID id)
	{
		if(!_cache.count(id))
			Core::log::report(FATAL_ERROR, "Shaders Library : wrong shader ID '%d'", id);
		return _cache[id];
	}

	ShaderID ShadersLibrary::addShaderToLibrary(std::shared_ptr<Shader> shader)
	{
		_cache[_current_id] = std::move(shader);
		_current_id++;
		return _current_id - 1;
	}

	void ShadersLibrary::removeShaderFromLibrary(ShaderID id)
	{
		if(_cache.count(id))
			_cache.erase(id);
	}

	void ShadersLibrary::clearLibrary()
	{
		for(auto [id, shader] : _cache)
		{
			shader->destroyModule();
			shader->destroy();
		}
		_cache.clear();
	}
}
