// This file is a part of Akel
// CREATED : 05/06/2021
// UPDATED : 05/06/2021

#ifndef __AK_VK_QUEUES__
#define __AK_VK_QUEUES__

#include <Akpch.h>

#include <Renderer/surface.h>

namespace Ak
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

#endif // __AK_VK_QUEUES__

