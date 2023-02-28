// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/02/2023
// Updated : 28/02/2023

#include <Core/log.h>
#include <Renderer/Images/texture_library.h>

namespace Ak
{
	std::shared_ptr<Texture> TextureLibrary::getTexture(TextureID id)
	{
		if(!_cache.count(id))
			Core::log::report(FATAL_ERROR, "Texture Library : wrong texture ID '%d'", id);
		return _cache[id];
	}

	TextureID TextureLibrary::addTextureToLibrary(std::filesystem::path texture)
	{
		_cache[_current_id] = create_shared_ptr_w<Texture>(loadTextureFromFile(std::move(texture)));
		_current_id++;
		return _current_id - 1;
	}

	TextureID TextureLibrary::addTextureToLibrary(std::shared_ptr<Texture> texture)
	{
		_cache[_current_id] = std::move(texture);
		_current_id++;
		return _current_id - 1;
	}

	void TextureLibrary::removeTextureFromLibrary(TextureID id)
	{
		if(_cache.count(id))
		{
			_cache[id]->destroy();
			_cache.erase(id);
		}
	}

	void TextureLibrary::clearLibrary()
	{
		for(auto [id, texture] : _cache)
			texture->destroy();
		_cache.clear();
	}
}
