// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/02/2023
// Updated : 05/09/2023

#ifndef __AK_CUBEMAP__
#define __AK_CUBEMAP__

#include <Akpch.h>
#include "vk_image.h"

namespace Ak
{
	struct CubemapParts
	{
		std::filesystem::path top;
		std::filesystem::path bottom;
		std::filesystem::path left;
		std::filesystem::path right;
		std::filesystem::path front;
		std::filesystem::path back;
	};

	class AK_API Cubemap : public Image
	{
		public:
			Cubemap() = default;
			void create(uint8_t* pixels, uint32_t width, uint32_t height, VkFormat format);
			~Cubemap() = default;
	};

	Cubemap loadCubemapFromFile(const std::filesystem::path& file);
	Cubemap loadCubemapFromFiles(CubemapParts parts);
}

#endif
