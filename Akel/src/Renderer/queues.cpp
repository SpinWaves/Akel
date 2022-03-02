// This file is a part of Akel
// Author : @kbz_8
// CREATED : 05/06/2021
// UPDATED : 28/02/2022

#include <Renderer/rendererComponent.h>

namespace Ak
{
    QueueFamilyIndices RendererComponent::findQueueFamilies(VkPhysicalDevice device)
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
