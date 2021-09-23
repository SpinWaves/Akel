// This file is a part of Akel
// CREATED : 05/06/2021
// UPDATED : 23/09/2021

#ifndef __AK_VK_LOWEST_INHERITANCE__
#define __AK_VK_LOWEST_INHERITANCE__

#include <Akpch.h>
const int MAX_FRAMES_IN_FLIGHT = 2;

namespace Ak
{
	class LowestInheritance
	{
		public:
			VkInstance instance;

			VkDevice device;
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

			SDL_Window* window;

			VkFormat swapChainImageFormat;

			VkSurfaceKHR surface;

            VkCommandPool commandPool;

            VkQueue graphicsQueue;
	};
}

#endif // __AK_VK_LOWEST_INHERITANCE__
