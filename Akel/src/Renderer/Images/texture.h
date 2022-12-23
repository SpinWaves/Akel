// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/12/2022
// Updated : 22/12/2022

#ifndef __AK_TEXTURE__
#define __AK_TEXTURE__

#include <Akpch.h>
#include "vk_image.h"

namespace Ak
{
	class Texture : public Image
	{
		public:
			Texture() = default;

			void create(std::vector<uint32_t> pixels, uint32_t width, uint32_t height);
			void createFromFile(std::filesystem::path path);

			~Texture() = default;

		private:
	};
}

#endif
