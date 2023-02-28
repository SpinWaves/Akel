// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/02/2023
// Updated : 28/02/2023

#include <Core/log.h>
#include <Graphics/material_library.h>

namespace Ak
{
	std::shared_ptr<Material> MaterialLibrary::getMaterial(MaterialID id)
	{
		if(!_cache.count(id))
			Core::log::report(FATAL_ERROR, "Material Library : wrong material ID '%d'", id);
		return _cache[id];
	}

	MaterialID MaterialLibrary::addMaterialToLibrary(std::shared_ptr<Material> material)
	{
		_cache[_current_id] = std::move(material);
		_current_id++;
		return _current_id - 1;
	}

	MaterialID MaterialLibrary::addMaterialToLibrary(MaterialDesc material)
	{
		_cache[_current_id] = create_shared_ptr_w<Material>(material);
		_current_id++;
		return _current_id - 1;
	}

	void MaterialLibrary::removeMaterialFromLibrary(MaterialID id)
	{
		if(_cache.count(id))
			_cache.erase(id);
	}

	void MaterialLibrary::clearLibrary()
	{
		_cache.clear();
	}
}
