// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 27/01/2023

#include <Renderer/Core/render_core.h>

namespace Ak
{
	Queues::QueueFamilyIndices Queues::findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
    {
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		_families = Queues::QueueFamilyIndices{};

		int i = 0;
		for(const auto& queueFamily : queueFamilies)
		{
			if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				_families->graphicsFamily = i;

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

			if(presentSupport)
				_families->presentFamily = i;

			if(_families->isComplete())
				break;
			i++;
		}
		return *_families;
	}

	void Queues::init()
	{
		if(!_families.has_value())
		{
			SDL_Window* window = SDL_CreateWindow("", 0, 0, 1, 1, SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN);
			if(!window)
				Core::log::report(FATAL_ERROR, "Vulkan : failed to create a window to init queues");

			VkSurfaceKHR surface = VK_NULL_HANDLE;
			if(SDL_Vulkan_CreateSurface(window, Render_Core::get().getInstance().get(), &surface) != SDL_TRUE)
				Core::log::report(FATAL_ERROR, "Vulkan : failed to create a surface to init queues");

			findQueueFamilies(Render_Core::get().getDevice().getPhysicalDevice(), surface);

			vkDestroySurfaceKHR(Render_Core::get().getInstance().get(), surface, nullptr);
			SDL_DestroyWindow(window);
		}
		vkGetDeviceQueue(Render_Core::get().getDevice().get(), _families->graphicsFamily.value(), 0, &_graphicsQueue);
		vkGetDeviceQueue(Render_Core::get().getDevice().get(), _families->presentFamily.value(), 0, &_presentQueue);
	}
}
