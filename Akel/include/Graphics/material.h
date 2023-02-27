// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/02/2023
// Updated : 27/02/2023

#ifndef __AK_MATERIAL__
#define __AK_MATERIAL__

#include <Akpch.h>
#include <Renderer/Images/texture_library.h>
#include <Renderer/Pipeline/shader_library.h>

namespace Ak
{
	struct AK_API MaterialTextures
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
			Material(ShaderID shader, MaterialTextures textures);

			void setAlbedoTexture(std::filesystem::path texture);
			//void setMetallicTexture(TextureID texture);
			//void setRoughnessTexture(TextureID texture);
			//void setNormalTexture(TextureID texture);

		private:
			void updateDescriptors();

			TextureID albedo = nulltexture;
			//TextureID normal;
			//TextureID metallic;
			//TextureID roughness;
			ShaderID _shader = nullshader;
			ShaderID _shader_cache = nullshader;
	};
}

#endif
