// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/02/2023
// Updated : 03/03/2023

#ifndef __AK_MATERIAL__
#define __AK_MATERIAL__

#include <Akpch.h>
#include <Renderer/Images/texture_library.h>
#include <Renderer/Pipeline/shaders_library.h>
#include <Renderer/Descriptors/vk_descriptor_set.h>

namespace Ak
{
	struct AK_API MaterialDesc
	{
		std::filesystem::path albedo;
		//std::filesystem::path normal;
		//std::filesystem::path metallic;
		//std::filesystem::path roughness;
	};

	class AK_API Material
	{
		friend class SceneRenderer;
		public:
			Material() = default;
			Material(MaterialDesc textures);

			void setAlbedoTexture(std::filesystem::path texture);
			//void setMetallicTexture(TextureID texture);
			//void setRoughnessTexture(TextureID texture);
			//void setNormalTexture(TextureID texture);

		private:
			void updateDescriptors(ShaderID shader);

			DescriptorSet _set;
			TextureID _albedo = nulltexture;
			//TextureID _normal;
			//TextureID _metallic;
			//TextureID _roughness;
			ShaderID _shader_cache = nullshader;
	};
}

#endif
