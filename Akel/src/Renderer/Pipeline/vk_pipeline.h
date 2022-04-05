// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 05/04/2022

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
			void init();
			inline void destroy() noexcept 
			{
				vkDestroyPipeline(Render_Core::get().getDevice()->get(), _graphicsPipeline, nullptr);
				vkDestroyPipelineLayout(Render_Core::get().getDevice()->get(), _pipelineLayout, nullptr);
			}

		private:
			VkPipelineLayout _pipelineLayout;
			VkPipeline _graphicsPipeline;
			VkPipelineCache _cache;
	};
}

#endif // __AK_VK_PIPELINE__
