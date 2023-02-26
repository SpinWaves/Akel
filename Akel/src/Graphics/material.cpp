// This file is a part of Akel
// Authors : @kbz_8
// Created : 25/02/2023
// Updated : 25/02/2023

#include <Graphics/material.h>
#include <Renderer/Pipeline/shader_library.h>
#include <Renderer/Images/texture_library.h>

namespace Ak
{
	Material::Material(ShaderID shader, MaterialTextures textures) : _shader(shader), _textures(textures) {}

	void Material::setAlbedoTexture(TextureID texture)
	{
		if(texture != _textures.albedo)
			_textures.albedo = texture;
	}

	void Material::updateDescriptors()
	{
		if(_shader == nullshader)
			return;
		
		auto shader = ShaderLibrary::get().getShader(_shader);
		auto albedo = TextureLibrary::get().getTexture(_textures.albedo);

		static DescriptorSet material_set;
		static Shader::ImageSampler albedo_sampler_cache;

		if(_shader != _shader_cache && shader->getImageSamplers().size() > 0)
		{
			if(shader->getImageSamplers().count("u_albedo_map"))
			{
				albedo_sampler_cache = shader->getImageSamplers()["u_albedo_map"];
				material_set = shader->getDescriptorSets()[albedo_sampler_cache.getSet()];
			}
			_shader_cache = _shader;
		}

		material_set.writeDescriptor(albedo_sampler_cache.getBinding(), albedo->getImageView(), albedo->getSampler());
	}
}
