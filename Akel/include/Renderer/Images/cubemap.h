// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/02/2023
// Updated : 06/09/2023

#ifndef __AK_CUBEMAP__
#define __AK_CUBEMAP__

#include <Akpch.h>
#include "vk_image.h"

namespace Ak
{
	class AK_API Cubemap : public Image
	{
		public:
			Cubemap() = default;
			void create(uint8_t* pixels, uint32_t width, uint32_t height, VkFormat format);
			~Cubemap() = default;
	};

	Cubemap loadCubemapFromFile(const std::filesystem::path& file);
}

#endif
