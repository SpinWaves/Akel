// This file is a part of AtlasEngine
// CREATED : 05/06/2021
// UPDATED : 05/06/2021

#ifndef __AE_VK_COMMAND_BUFFER__
#define __AE_VK_COMMAND_BUFFER__

#include <AEpch.h>

#include <Renderer/pipeline.h>

namespace AE
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

#endif // __AE_VK_COMMAND_BUFFER__

