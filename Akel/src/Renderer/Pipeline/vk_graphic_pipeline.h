// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 05/04/2022

#ifndef __AK_VK_GRAPHIC_PIPELINE__
#define __AK_VK_GRAPHIC_PIPELINE__

#include <Akpch.h>
#include "vk_shader.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
	class GraphicPipeline
	{
		public:
			void init();
			inline void destroy() noexcept
			{
				static_assert(_pipeline != VK_NULL_HANDLE, "trying to destroy an uninit pipeline");
				vkDestroyPipeline(Render_Core::get().getDevice()->get(), _graphicsPipeline, nullptr);
				
				static_assert(_pipelineLayout != VK_NULL_HANDLE, "trying to destroy an uninit pipeline layout");
				vkDestroyPipelineLayout(Render_Core::get().getDevice()->get(), _pipelineLayout, nullptr);
			}

		private:
			VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
			VkPipeline _graphicsPipeline = VK_NULL_HANDLE;
			VkPipelineCache _cache;
	};
}

#endif // __AK_VK_GRAPHIC_PIPELINE__
