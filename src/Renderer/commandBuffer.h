// This file is a part of Akel
// CREATED : 05/06/2021
// UPDATED : 05/06/2021

#ifndef __AK_VK_COMMAND_BUFFER__
#define __AK_VK_COMMAND_BUFFER__

#include <Akpch.h>

#include <Renderer/pipeline.h>

namespace Ak
{
	class CommandBuffer : public Pipeline
	{
		public:
			CommandBuffer();

            void createCommandPool();
            void createCommandBuffers();

            VkCommandPool commandPool;
            std::vector<VkCommandBuffer> commandBuffers;
	};
}

#endif // __AK_VK_COMMAND_BUFFER__

