// This file is a part of AtlasEngine
// CREATED : 05/06/2021
// UPDATED : 05/06/2021

#ifndef __AE_VK_QUEUES__
#define __AE_VK_QUEUES__

#include <AEpch.h>

#include <Renderer/surface.h>

namespace AE
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

	class Queues : virtual public Surface
	{
		public:
			Queues();
            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	
            VkQueue graphicsQueue;
            VkQueue presentQueue;
	};
}

#endif // __AE_VK_QUEUES__

