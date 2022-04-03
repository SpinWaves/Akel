// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 03/04/2022

#include "vk_queues.h"

namespace Ak
{
	QueueFamilyIndices Queues::findQueueFamilies(VkPhysicalDevice device)
    {
		Queues::QueueFamilyIndices indices;

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
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, Render_Core::get().getSurface()->get(), &presentSupport);

			if(presentSupport)
				indices.presentFamily = i;

			if(indices.isComplete())
				break;
			i++;
		}

		return indices;
	}
}
