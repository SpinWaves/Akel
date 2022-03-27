// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2022
// Updated : 27/03/2022

#ifndef __AK_VK_PIPELINE__
#define __AK_VK_PIPELINE__

#include "shaders.h"

namespace Ak
{
	class CommandBuffer;

	class Pipeline
	{
		public:
			Pipeline() = default;

			inline void bindPipeline(const CommandBuffer& commandBuffer) const { vkCmdBindPipeline(commandBuffer, GetPipelineBindPoint(), GetPipeline()); }
			virtual Shader* getShader() const = 0;
			virtual const VkDescriptorSetLayout& getDescriptorSetLayout() const = 0;
			virtual const VkDescriptorPool& getDescriptorPool() const = 0;
			virtual const VkPipeline& getPipeline() const = 0;
			virtual const VkPipelineLayout& getPipelineLayout() const = 0;
			virtual const VkPipelineBindPoint& getPipelineBindPoint() const = 0;

			virtual ~Pipeline() = default;
	};
}

#endif // __AK_VK_PIPELINE__
