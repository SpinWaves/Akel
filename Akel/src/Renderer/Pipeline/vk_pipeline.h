// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 04/04/2022

#ifndef __AK_VK_PIPELINE__
#define __AK_VK_PIPELINE__

#include <Akpch.h>
#include "vk_shader.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
	class Pipeline
	{
		public:

		private:
			VkPipelineLayout _pipelineLayout;
			VkPipeline _graphicsPipeline;
	};
}

#endif // __AK_VK_PIPELINE__
