// This file is a part of Akel
// Authors : @kbz_8
// Created : 13/01/2023
// Updated : 17/08/2023

#ifndef __AK_DEPTH_IMAGE__
#define __AK_DEPTH_IMAGE__

#include <Akpch.h>
#include "vk_image.h"

namespace Ak
{
	class DepthImage : public Image
	{
		public:
			void create(class RendererComponent& renderer, uint32_t width, uint32_t height);
	};
}

#endif
