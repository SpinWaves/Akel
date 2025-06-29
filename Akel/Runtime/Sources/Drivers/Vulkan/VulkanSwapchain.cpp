// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/Vulkan/VulkanSwapchain.h>
#include <Drivers/Vulkan/VulkanDevice.h>
#include <Drivers/Vulkan/VulkanSurface.h>

namespace Ak
{
	VulkanSwapchain::VulkanSwapchain(VulkanDevice& device, SharedPtr<VulkanSurface> surface, Vec2ui extent, bool vsync, bool priorise_srgb) : m_device(device)
	{
	}

	VulkanSwapchain::SwapchainSupportDetails VulkanSwapchain::QuerySwapchainSupport(SharedPtr<VulkanSurface> surface)
	{
		VulkanSwapchain::SwapchainSupportDetails details;

		if(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_device.Get(), surface->Get(), &details.capabilities) != VK_SUCCESS)
			FatalError("Vulkan : unable to retrieve surface capabilities");

		std::uint32_t format_count = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(m_device.Get(), surface->Get(), &format_count, nullptr);

		if(format_count != 0)
		{
			details.formats.resize(format_count);
			vkGetPhysicalDeviceSurfaceFormatsKHR(m_device.Get(), surface->Get(), &format_count, details.formats.data());
		}

		std::uint32_t present_mode_count;
		vkGetPhysicalDeviceSurfacePresentModesKHR(m_device.Get(), surface->Get(), &present_mode_count, nullptr);

		if(present_mode_count != 0)
		{
			details.present_modes.resize(present_mode_count);
			vkGetPhysicalDeviceSurfacePresentModesKHR(m_device.Get(), surface->Get(), &present_mode_count, details.present_modes.data());
		}

		return details;
	}

	VulkanSwapchain::~VulkanSwapchain()
	{
	}
}
