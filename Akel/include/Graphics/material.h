// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/02/2023
// Updated : 05/11/2023

#ifndef __AK_MATERIAL__
#define __AK_MATERIAL__

#include <Akpch.h>
#include <Renderer/Images/texture_library.h>
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
		friend class ForwardPass;
		public:
			Material() = default;
			Material(MaterialDesc textures);

			void setAlbedoTexture(const std::filesystem::path& texture);
			//void setMetallicTexture(TextureID texture);
			//void setRoughnessTexture(TextureID texture);
			//void setNormalTexture(TextureID texture);

		private:
			void updateDescriptors(const DescriptorSet& set, bool rebuild);

		private:
			DescriptorSet _set; // duplicated set
			TextureID _albedo = nulltexture;
			//TextureID _normal;
			//TextureID _metallic;
			//TextureID _roughness;
	};
}

#endif
