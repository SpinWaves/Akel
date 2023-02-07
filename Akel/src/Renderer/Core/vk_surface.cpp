// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 27/01/2023

#include <Renderer/Core/render_core.h>
#include <Platform/window.h>
#include <Utils/assert.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
	void Surface::create(RendererComponent& renderer)
	{
		if(SDL_Vulkan_CreateSurface(renderer.getWindow()->getNativeWindow(), Render_Core::get().getInstance().get(), &_surface) != SDL_TRUE)
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

	void Surface::destroy() noexcept
	{
		Ak_assert(_surface != VK_NULL_HANDLE, "trying to destroy an uninit surface");
		vkDestroySurfaceKHR(Render_Core::get().getInstance().get(), _surface, nullptr);
	}
}
