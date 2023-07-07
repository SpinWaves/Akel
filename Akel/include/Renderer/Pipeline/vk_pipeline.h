// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/04/2022
// Updated : 02/07/2023

#ifndef __AK_VK_PIPELINE__
#define __AK_VK_PIPELINE__

#include <Akpch.h>
#include <Renderer/Command/vk_cmd_buffer.h>

namespace Ak
{
	class Pipeline
	{
		public:
			inline virtual bool bindPipeline(CmdBuffer& commandBuffer) noexcept { vkCmdBindPipeline(commandBuffer.get(), getPipelineBindPoint(), getPipeline()); return true; }
			inline virtual void endPipeline(CmdBuffer& commandBuffer) noexcept {};

			virtual const VkPipeline& getPipeline() const = 0;
			virtual const VkPipelineLayout& getPipelineLayout() const = 0;
			virtual const VkPipelineBindPoint& getPipelineBindPoint() const = 0;

			virtual ~Pipeline() = default;
	};
}

#endif // __AK_VK_PIPELINE__
