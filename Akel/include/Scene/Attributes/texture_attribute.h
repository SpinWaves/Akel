// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2023
// Updated : 18/02/2023

#ifndef __AK_TEXTURE_ATTRIBUTE__
#define __AK_TEXTURE_ATTRIBUTE__

#include <Akpch.h>
#include <Maths/vec4.h>
#include <Renderer/Images/texture.h>

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

			inline std::shared_ptr<Texture> getTexture() { return _texture; }

		private:
			void VulkanInitTexture() noexcept;
			void VulkanDestroyTexture() noexcept;

			std::filesystem::path _texture_path;
			std::shared_ptr<Texture> _texture;
	};
}

#endif
