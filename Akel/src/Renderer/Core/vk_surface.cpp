// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 03/04/2022

#include "vk_surface.h"

namespace Ak
{
	void Surface::createSurface()
	{
		if(SDL_Vulkan_CreateSurface(Render_Core::get().getWindow()->getNativeWindow(), Render_Core::get().getInstance()->get(), &_surface) != SDL_TRUE)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create a surface : %s", SDL_GetError());
	}

	VkSurfaceFormatKHR Surface::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for(const auto& availableFormat : availableFormats)
		{
			if(availableFormat.format == VK_FORMAT_R8G8B8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return availableFormat;
		}

		return availableFormats[0];
	}
}
