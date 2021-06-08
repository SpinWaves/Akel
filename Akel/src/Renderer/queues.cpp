// This file is a part of Akel
// CREATED : 05/06/2021
// UPDATED : 05/06/2021

#include <Renderer/renderer.h>

namespace Ak
{
	Queues::Queues() : Surface() {}

    QueueFamilyIndices Queues::findQueueFamilies(VkPhysicalDevice device) 
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for(const auto& queueFamily : queueFamilies)
        {
            if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                indices.graphicsFamily = i;

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if(presentSupport)
                indices.presentFamily = i;

            if(indices.isComplete())
                break;
            i++;
        }

        return indices;
    }
}

