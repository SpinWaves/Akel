// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/04/2022
// Updated : 17/04/2022

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
			inline void bindPipeline(const CommandBuffer& commandBuffer) const noexcept { vkCmdBindPipeline(commandBuffer, getPipelineBindPoint(), getPipeline()); }

			virtual const Shader& getShader() const = 0;
			virtual const VkPipeline& getPipeline() const = 0;
			virtual const VkPipelineLayout& getPipelineLayout() const = 0;
			
			virtual ~Pipeline() = default;
	};
}

#endif // __AK_VK_PIPELINE__
