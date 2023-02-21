// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2023
// Updated : 21/02/2023

#include <Scene/Attributes/texture_attribute.h>
#include <Core/Memory/sharedPtrWrapper.h>

namespace Ak
{
	void TextureAttribute::VulkanInitTexture() noexcept
	{
		if(!_texture_path.empty())
		{
			std::shared_ptr<Texture> texture = create_shared_ptr_w<Texture>(loadTextureFromFile(_texture_path));
			_texture_id = TextureLibrary::get().addTextureToLibrary(std::move(texture));
		}
	}
}
