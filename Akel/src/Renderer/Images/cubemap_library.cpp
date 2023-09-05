// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/09/2023
// Updated : 05/09/2023

#include <Core/log.h>
#include <Renderer/Images/cubemap_library.h>

namespace Ak
{
	std::shared_ptr<Cubemap> CubemapLibrary::getCubemap(CubemapID id)
	{
		if(!_cache.count(id))
			Core::log::report(FATAL_ERROR, "Cubemap Library : wrong cubemap ID '%d'", id);
		return _cache[id];
	}

	CubemapID CubemapLibrary::addCubemapToLibrary(const std::filesystem::path& cubemap)
	{
		_cache[_current_id] = create_shared_ptr_w<Cubemap>(loadCubemapFromFile(cubemap));
		_current_id++;
		return _current_id - 1;
	}

	CubemapID CubemapLibrary::addCubemapToLibrary(CubemapParts cubemap)
	{
		_cache[_current_id] = create_shared_ptr_w<Cubemap>(loadCubemapFromFiles(std::move(cubemap)));
		_current_id++;
		return _current_id - 1;
	}

	CubemapID CubemapLibrary::addCubemapToLibrary(std::shared_ptr<Cubemap> cubemap)
	{
		_cache[_current_id] = std::move(cubemap);
		_current_id++;
		return _current_id - 1;
	}

	void CubemapLibrary::removeCubemapFromLibrary(CubemapID id)
	{
		if(_cache.count(id))
		{
			_cache[id]->destroy();
			_cache.erase(id);
		}
	}

	void CubemapLibrary::clearLibrary()
	{
		for(auto [id, cubemap] : _cache)
			cubemap->destroy();
		_cache.clear();
	}
}
