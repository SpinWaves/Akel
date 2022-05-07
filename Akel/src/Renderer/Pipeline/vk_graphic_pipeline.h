// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 29/04/2022

#ifndef __AK_VK_GRAPHIC_PIPELINE__
#define __AK_VK_GRAPHIC_PIPELINE__

#include "vk_pipeline.h"

namespace Ak
{
	class GraphicPipeline : public Pipeline
	{
		public:
			void init();
			inline void destroy() noexcept
			{
				Ak_assert(_pipeline != VK_NULL_HANDLE, "trying to destroy an uninit pipeline");
				vkDestroyPipeline(Render_Core::get().getDevice().get(), _graphicsPipeline, nullptr);				
			}

			inline const Shader& getShader() const override { return _shader; }
			inline const VkPipeline& getPipeline() const override { return _graphicsPipeline; }
			inline const VkPipelineLayout& getPipelineLayout() const override { return _pipelineLayout; }

		private:
			VkPipeline _graphicsPipeline = VK_NULL_HANDLE;
			VkPipelineCache _cache = VK_NULL_HANDLE;

			Shader _shader;
	};
}

#endif // __AK_VK_GRAPHIC_PIPELINE__
