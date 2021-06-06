// This file is a part of AtlasEngine
// CREATED : 05/06/2021
// UPDATED : 05/06/2021

#ifndef __AE_VK_LOWEST_INHERITANCE__
#define __AE_VK_LOWEST_INHERITANCE__

#include <AEpch.h>

namespace AE
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
	};
}

#endif // __AE_VK_LOWEST_INHERITANCE__

