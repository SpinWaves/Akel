// This file is a part of Akel
// Authors : @kbz_8
// Created : 25/02/2023
// Updated : 07/11/2023

#include <Graphics/material.h>
#include <Renderer/Pipeline/shaders_library.h>

namespace Ak
{
	Material::Material(MaterialDesc textures)
	{
		_albedo = TextureLibrary::get().addTextureToLibrary(textures.albedo);
	}

	void Material::setAlbedoTexture(const std::filesystem::path& texture)
	{
		_albedo = TextureLibrary::get().addTextureToLibrary(texture);
	}

	void Material::updateDescriptors(const DescriptorSet& set, bool rebuild)
	{
		auto albedo = TextureLibrary::get().getTexture(_albedo);

		if(rebuild)
		{
			if(_set.isInit())
				_set.destroy();
			_set = set.duplicate();
		}

		if(albedo != nullptr && _set.isInit())
			_set.writeDescriptor(0, albedo->getImageView(), albedo->getSampler());
	}
}
