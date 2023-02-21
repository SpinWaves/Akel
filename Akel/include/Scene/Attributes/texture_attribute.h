// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2023
// Updated : 21/02/2023

#ifndef __AK_TEXTURE_ATTRIBUTE__
#define __AK_TEXTURE_ATTRIBUTE__

#include <Akpch.h>
#include <Maths/vec4.h>
#include <Renderer/Images/texture_library.h>

namespace Ak
{
	class AK_API TextureAttribute
	{
		public:
			Maths::Vec4f color = { 1.0f, 1.0f, 1.0f, 1.0f };

			TextureAttribute() = default;
			TextureAttribute(std::filesystem::path texture) : _texture_path(std::move(texture))
			{
				VulkanInitTexture();
			}

			inline TextureID getTextureID() { return _texture_id; }

		private:
			void VulkanInitTexture() noexcept;

			std::filesystem::path _texture_path;
			TextureID _texture_id;
	};
}

#endif
