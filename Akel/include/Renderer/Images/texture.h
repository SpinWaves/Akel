// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/12/2022
// Updated : 30/01/2023

#ifndef __AK_TEXTURE__
#define __AK_TEXTURE__

#include <Akpch.h>
#include "vk_image.h"
#include <Renderer/Buffers/vk_buffer.h>

namespace Ak
{
	class Texture : public Image
	{
		public:
			Texture() = default;

			void create(uint8_t* pixels, uint32_t width, uint32_t height, VkFormat format);

			~Texture() = default;

		private:
			Buffer _buffer;

	};

	Texture loadTextureFromFile(std::filesystem::path path);
}

#endif
