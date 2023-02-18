// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2023
// Updated : 18/02/2023

#include <Scene/Attributes/texture_attribute.h>

namespace Ak
{
	void TextureAttribute::VulkanInitTexture() noexcept
	{
		if(!_texture_path.empty())
			_texture = create_shared_ptr_w<Texture>(loadTextureFromFile(_texture_path));
	}

	void TextureAttribute::VulkanDestroyTexture() noexcept
	{
		if(!_texture_path.empty())
			_texture->destroy();
	}
}
