// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2023
// Updated : 12/02/2023

#ifndef __AK_TEXTURE_ATTRIBUTE__
#define __AK_TEXTURE_ATTRIBUTE__

#include <Akpch.h>
#include <Maths/vec4.h>
#include <Renderer/Images/texture.h>

namespace Ak
{
	class TextureAttribute
	{
		friend class Scene;

		public:
			Vec4f color = { 1.0f, 1.0f, 1.0f, 1.0f };

			TextureAttribute() = default;
			TextureAttribute(std::filesystem::path texture) : _texture_path(std::move(_texture)) {}

		private:
			void VulkanInitTexture() noexcept;
			void VulkanDestroyTexture() noexcept;

			std::filesystem::path _texture_path;
			Texture _texture;
	};
}

#endif
