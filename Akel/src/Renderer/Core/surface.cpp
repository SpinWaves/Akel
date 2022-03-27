// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2022
// Updated : 27/03/2022

#include "render_core.h"

namespace Ak
{
	Surface::Surface(const Instance* instance, const PhysicalDevice* physicalDevice) : _instance(instance), _physicalDevice(physicalDevice)
	{
		// Creates the surface.
		if(SDL_Vulkan_CreateSurface(_instance->getHandledWindow()->getNativeWindow(), _instance, &_surface) != SDL_TRUE)
            Core::log::report(FATAL_ERROR, "Vulkan : Failed to create a surface : %s", SDL_GetError());
		
		RCore::checkVk(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*_physicalDevice, _surface, &_capabilities));

		uint32_t surfaceFormatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(*_physicalDevice, _surface, &surfaceFormatCount, nullptr);
		std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(*_physicalDevice, _surface, &surfaceFormatCount, surfaceFormats.data());

		if(surfaceFormatCount == 1 && surfaceFormats[0].format == VK_FORMAT_UNDEFINED)
		{
			_format.format = VK_FORMAT_B8G8R8A8_UNORM;
			_format.colorSpace = surfaceFormats[0].colorSpace;
		}
		else
		{
			// Iterate over the list of available surface format and
			// check for the presence of VK_FORMAT_B8G8R8A8_UNORM
			bool found_B8G8R8A8_UNORM = false;

			for(auto &surfaceFormat : surfaceFormats)
			{
				if(surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM)
				{
					_format.format = surfaceFormat.format;
					_format.colorSpace = surfaceFormat.colorSpace;
					found_B8G8R8A8_UNORM = true;
					break;
				}
			}

			// In case VK_FORMAT_B8G8R8A8_UNORM is not available
			// select the first available color format
			if(!found_B8G8R8A8_UNORM)
			{
				_format.format = surfaceFormats[0].format;
				_format.colorSpace = surfaceFormats[0].colorSpace;
			}
		}
	}

	Surface::~Surface()
	{
		vkDestroySurfaceKHR(*_instance, _surface, nullptr);
	}
}
