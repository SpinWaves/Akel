// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 08/05/2022

#ifndef __AK_VK_GRAPHIC_PIPELINE__
#define __AK_VK_GRAPHIC_PIPELINE__

#include "vk_pipeline.h"

namespace Ak
{
	class GraphicPipeline : public Pipeline
	{
		public:
			void init();
			void destroy() noexcept;

			inline const Shader& getShader() const override { return *_shader; }
			inline const VkPipeline& getPipeline() const override { return _graphicsPipeline; }
			inline const VkPipelineLayout& getPipelineLayout() const override { return _pipelineLayout; }
			inline const VkPipelineBindPoint& getPipelineBindPoint() const override { return _pipelineBindPoint; }

		private:
			Shader* _shader = nullptr;
			VkPipeline _graphicsPipeline = VK_NULL_HANDLE;
			VkPipelineCache _cache = VK_NULL_HANDLE;
			VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
			VkPipelineBindPoint _pipelineBindPoint;

	};
}

#endif // __AK_VK_GRAPHIC_PIPELINE__
