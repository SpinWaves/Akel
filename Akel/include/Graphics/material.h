// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/02/2023
// Updated : 26/02/2023

#ifndef __AK_MATERIAL__
#define __AK_MATERIAL__

#include <Akpch.h>
#include <Renderer/Images/texture_library.h>
#include <Renderer/Pipeline/shader_library.h>

namespace Ak
{
	struct AK_API MaterialTextures
	{
		TextureID albedo = nulltexture;
		//TextureID normal;
		//TextureID metallic;
		//TextureID roughness;
	};

	class AK_API Material
	{
		friend class SceneRenderer;
		public:
			Material() = default;
			Material(ShaderID shader, MaterialTextures textures);

			void setAlbedoTexture(TextureID texture);
			//void setMetallicTexture(TextureID texture);
			//void setRoughnessTexture(TextureID texture);
			//void setNormalTexture(TextureID texture);

		private:
			void updateDescriptors();

			MaterialTextures _textures;
			ShaderID _shader = nullshader;
			ShaderID _shader_cache = nullshader;
	};
}

#endif
