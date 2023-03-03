// This file is a part of Akel
// Authors : @kbz_8
// Created : 25/02/2023
// Updated : 03/03/2023

#include <Graphics/material.h>
#include <Renderer/Pipeline/shaders_library.h>

namespace Ak
{
	Material::Material(MaterialDesc textures)
	{
		_albedo = TextureLibrary::get().addTextureToLibrary(textures.albedo);
	}

	void Material::setAlbedoTexture(std::filesystem::path texture)
	{
		_albedo = TextureLibrary::get().addTextureToLibrary(std::move(texture));
	}

	void Material::updateDescriptors(ShaderID shader_id)
	{
		if(shader_id == nullshader)
			return;
		
		auto shader = ShadersLibrary::get().getShader(shader_id);
		auto albedo = TextureLibrary::get().getTexture(_albedo);

		static Shader::ImageSampler albedo_sampler_cache;

		if(shader_id != _shader_cache && shader->getImageSamplers().size() > 0)
		{
			if(shader->getImageSamplers().count("u_albedo_map"))
			{
				albedo_sampler_cache = shader->getImageSamplers()["u_albedo_map"];
				_set = shader->getDescriptorSets()[albedo_sampler_cache.getSet()].duplicate();
			}
			_shader_cache = shader_id;
		}

		if(albedo != nullptr && _set.isInit())
			_set.writeDescriptor(albedo_sampler_cache.getBinding(), albedo->getImageView(), albedo->getSampler());
	}
}
