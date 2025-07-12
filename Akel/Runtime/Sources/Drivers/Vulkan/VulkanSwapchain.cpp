// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/Vulkan/VulkanSwapchain.h>
#include <Drivers/Vulkan/VulkanDevice.h>
#include <Drivers/Vulkan/VulkanSurface.h>
#include <Drivers/Vulkan/VulkanInstance.h>
#include <Drivers/Vulkan/VulkanAdapter.h>

namespace Ak
{
	std::string VulkanFormatName(VkFormat format);

	VulkanSwapchain::VulkanSwapchain(VulkanDevice& device, SharedPtr<VulkanSurface> surface, Vec2ui extent, bool vsync, bool priorise_srgb) : m_device(device)
	{
		SwapchainSupportDetails details = QuerySwapchainSupport(surface);

		VkSurfaceFormatKHR surface_format = ChooseSurfaceFormat(details, priorise_srgb);
		VkPresentModeKHR present_mode = ChoosePresentMode(details, vsync);

		std::uint32_t image_count = details.capabilities.minImageCount + 1;
		if(details.capabilities.maxImageCount > 0 && image_count > details.capabilities.maxImageCount)
			image_count = details.capabilities.maxImageCount;

		std::array queue_family_indices{
			m_device.GetGraphicsQueueFamily(),
			m_device.GetPresentQueueFamily()
		};

		VkExtent2D vk_extent;

		if(details.capabilities.currentExtent.width == UINT32_MAX)
		{
			vk_extent.width = std::clamp(extent.x, details.capabilities.minImageExtent.width, details.capabilities.maxImageExtent.width);
			vk_extent.height = std::clamp(extent.y, details.capabilities.minImageExtent.height, details.capabilities.maxImageExtent.height);
		}
		else
			vk_extent = details.capabilities.currentExtent;

		VkSwapchainCreateInfoKHR create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		create_info.surface = surface->Get();
		create_info.minImageCount = image_count;
		create_info.imageFormat = surface_format.format;
		create_info.imageColorSpace = surface_format.colorSpace;
		create_info.imageExtent = vk_extent;
		create_info.imageArrayLayers = 1;
		create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		create_info.preTransform = details.capabilities.currentTransform;
		create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		create_info.presentMode = present_mode;
		create_info.clipped = VK_TRUE;
		create_info.oldSwapchain = VK_NULL_HANDLE;

		if(m_device.GetGraphicsQueueFamily() != m_device.GetPresentQueueFamily())
		{
			create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			create_info.queueFamilyIndexCount = queue_family_indices.size();
			create_info.pQueueFamilyIndices = queue_family_indices.data();
		}
		else
			create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

		CheckVk(m_device.vkCreateSwapchainKHR(m_device.Get(), &create_info, nullptr, &m_swapchain));

		DebugLog("Vulkan: created swapchain with format %", VulkanFormatName(VK_FORMAT_R8G8B8A8_SRGB));
	}

	VulkanSwapchain::SwapchainSupportDetails VulkanSwapchain::QuerySwapchainSupport(SharedPtr<VulkanSurface> surface)
	{
		VulkanSwapchain::SwapchainSupportDetails details;

		if(m_device.GetInstance().vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_device.GetAdapter()->Get(), surface->Get(), &details.capabilities) != VK_SUCCESS)
			FatalError("Vulkan: unable to retrieve surface capabilities");

		std::uint32_t format_count = 0;
		m_device.GetInstance().vkGetPhysicalDeviceSurfaceFormatsKHR(m_device.GetAdapter()->Get(), surface->Get(), &format_count, nullptr);

		if(format_count != 0)
		{
			details.formats.resize(format_count);
			m_device.GetInstance().vkGetPhysicalDeviceSurfaceFormatsKHR(m_device.GetAdapter()->Get(), surface->Get(), &format_count, details.formats.data());
		}

		std::uint32_t present_mode_count;
		m_device.GetInstance().vkGetPhysicalDeviceSurfacePresentModesKHR(m_device.GetAdapter()->Get(), surface->Get(), &present_mode_count, nullptr);

		if(present_mode_count != 0)
		{
			details.present_modes.resize(present_mode_count);
			m_device.GetInstance().vkGetPhysicalDeviceSurfacePresentModesKHR(m_device.GetAdapter()->Get(), surface->Get(), &present_mode_count, details.present_modes.data());
		}

		return details;
	}

	VkSurfaceFormatKHR VulkanSwapchain::ChooseSurfaceFormat(SwapchainSupportDetails& details, bool priorise_srgb)
	{
		if(details.formats.size() == 1 && details.formats[0].format == VK_FORMAT_UNDEFINED)
		{
			// If the list contains one undefined format, it means any format can be used
			VkSurfaceFormatKHR format;
			format.colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
			if(priorise_srgb)
				format.format = VK_FORMAT_R8G8B8A8_SRGB;
			else
				format.format = VK_FORMAT_R8G8B8A8_UNORM;
			return format;
			
		}

		auto is_format_srgb = [](VkFormat format)
		{
			switch(format)
			{
				case VK_FORMAT_R8G8B8A8_SRGB: // fallthrought
				case VK_FORMAT_B8G8R8A8_SRGB: return true;

				default: return false;
			}
			return false;
		};

		auto is_format_unorm = [](VkFormat format)
		{
			switch(format)
			{
				case VK_FORMAT_R8G8B8A8_UNORM: // fallthrought
				case VK_FORMAT_B8G8R8A8_UNORM: return true;

				default: return false;
			}
			return false;
		};

		for(auto& format : details.formats)
		{
			if(priorise_srgb)
			{
				if(is_format_srgb(format.format) && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
					return format;
			}
			else
			{
				if(is_format_unorm(format.format))
					return format;
			}
		}
		return details.formats[0];
	}

	VkPresentModeKHR VulkanSwapchain::ChoosePresentMode(SwapchainSupportDetails& details, bool try_vsync)
	{
		if(try_vsync)
			return VK_PRESENT_MODE_FIFO_KHR;
		bool mailbox_supported = false;
		bool immediate_supported = false;
		for(auto& mode : details.present_modes)
		{
			if(mode == VK_PRESENT_MODE_MAILBOX_KHR)
				mailbox_supported = true;
			if(mode == VK_PRESENT_MODE_IMMEDIATE_KHR)
				immediate_supported = true;
		}
		if(mailbox_supported)
			return VK_PRESENT_MODE_MAILBOX_KHR;
		if(immediate_supported)
			return VK_PRESENT_MODE_IMMEDIATE_KHR;  // Best mode for low latency
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VulkanSwapchain::~VulkanSwapchain()
	{
		m_device.vkDestroySwapchainKHR(m_device.Get(), m_swapchain, nullptr);
		DebugLog("Vulkan: destroyed swapchain");
	}

	std::string VulkanFormatName(VkFormat format)
	{
		#define STRINGIFY(x) case x: return #x

		switch(format)
		{
			STRINGIFY(VK_FORMAT_UNDEFINED);
			STRINGIFY(VK_FORMAT_R4G4_UNORM_PACK8);
			STRINGIFY(VK_FORMAT_R4G4B4A4_UNORM_PACK16);
			STRINGIFY(VK_FORMAT_B4G4R4A4_UNORM_PACK16);
			STRINGIFY(VK_FORMAT_R5G6B5_UNORM_PACK16);
			STRINGIFY(VK_FORMAT_B5G6R5_UNORM_PACK16);
			STRINGIFY(VK_FORMAT_R5G5B5A1_UNORM_PACK16);
			STRINGIFY(VK_FORMAT_B5G5R5A1_UNORM_PACK16);
			STRINGIFY(VK_FORMAT_A1R5G5B5_UNORM_PACK16);
			STRINGIFY(VK_FORMAT_R8_UNORM);
			STRINGIFY(VK_FORMAT_R8_SNORM);
			STRINGIFY(VK_FORMAT_R8_USCALED);
			STRINGIFY(VK_FORMAT_R8_SSCALED);
			STRINGIFY(VK_FORMAT_R8_UINT);
			STRINGIFY(VK_FORMAT_R8_SINT);
			STRINGIFY(VK_FORMAT_R8_SRGB);
			STRINGIFY(VK_FORMAT_R8G8_UNORM);
			STRINGIFY(VK_FORMAT_R8G8_SNORM);
			STRINGIFY(VK_FORMAT_R8G8_USCALED);
			STRINGIFY(VK_FORMAT_R8G8_SSCALED);
			STRINGIFY(VK_FORMAT_R8G8_UINT);
			STRINGIFY(VK_FORMAT_R8G8_SINT);
			STRINGIFY(VK_FORMAT_R8G8_SRGB);
			STRINGIFY(VK_FORMAT_R8G8B8_UNORM);
			STRINGIFY(VK_FORMAT_R8G8B8_SNORM);
			STRINGIFY(VK_FORMAT_R8G8B8_USCALED);
			STRINGIFY(VK_FORMAT_R8G8B8_SSCALED);
			STRINGIFY(VK_FORMAT_R8G8B8_UINT);
			STRINGIFY(VK_FORMAT_R8G8B8_SINT);
			STRINGIFY(VK_FORMAT_R8G8B8_SRGB);
			STRINGIFY(VK_FORMAT_B8G8R8_UNORM);
			STRINGIFY(VK_FORMAT_B8G8R8_SNORM);
			STRINGIFY(VK_FORMAT_B8G8R8_USCALED);
			STRINGIFY(VK_FORMAT_B8G8R8_SSCALED);
			STRINGIFY(VK_FORMAT_B8G8R8_UINT);
			STRINGIFY(VK_FORMAT_B8G8R8_SINT);
			STRINGIFY(VK_FORMAT_B8G8R8_SRGB);
			STRINGIFY(VK_FORMAT_R8G8B8A8_UNORM);
			STRINGIFY(VK_FORMAT_R8G8B8A8_SNORM);
			STRINGIFY(VK_FORMAT_R8G8B8A8_USCALED);
			STRINGIFY(VK_FORMAT_R8G8B8A8_SSCALED);
			STRINGIFY(VK_FORMAT_R8G8B8A8_UINT);
			STRINGIFY(VK_FORMAT_R8G8B8A8_SINT);
			STRINGIFY(VK_FORMAT_R8G8B8A8_SRGB);
			STRINGIFY(VK_FORMAT_B8G8R8A8_UNORM);
			STRINGIFY(VK_FORMAT_B8G8R8A8_SNORM);
			STRINGIFY(VK_FORMAT_B8G8R8A8_USCALED);
			STRINGIFY(VK_FORMAT_B8G8R8A8_SSCALED);
			STRINGIFY(VK_FORMAT_B8G8R8A8_UINT);
			STRINGIFY(VK_FORMAT_B8G8R8A8_SINT);
			STRINGIFY(VK_FORMAT_B8G8R8A8_SRGB);
			STRINGIFY(VK_FORMAT_A8B8G8R8_UNORM_PACK32);
			STRINGIFY(VK_FORMAT_A8B8G8R8_SNORM_PACK32);
			STRINGIFY(VK_FORMAT_A8B8G8R8_USCALED_PACK32);
			STRINGIFY(VK_FORMAT_A8B8G8R8_SSCALED_PACK32);
			STRINGIFY(VK_FORMAT_A8B8G8R8_UINT_PACK32);
			STRINGIFY(VK_FORMAT_A8B8G8R8_SINT_PACK32);
			STRINGIFY(VK_FORMAT_A8B8G8R8_SRGB_PACK32);
			STRINGIFY(VK_FORMAT_A2R10G10B10_UNORM_PACK32);
			STRINGIFY(VK_FORMAT_A2R10G10B10_SNORM_PACK32);
			STRINGIFY(VK_FORMAT_A2R10G10B10_USCALED_PACK32);
			STRINGIFY(VK_FORMAT_A2R10G10B10_SSCALED_PACK32);
			STRINGIFY(VK_FORMAT_A2R10G10B10_UINT_PACK32);
			STRINGIFY(VK_FORMAT_A2R10G10B10_SINT_PACK32);
			STRINGIFY(VK_FORMAT_A2B10G10R10_UNORM_PACK32);
			STRINGIFY(VK_FORMAT_A2B10G10R10_SNORM_PACK32);
			STRINGIFY(VK_FORMAT_A2B10G10R10_USCALED_PACK32);
			STRINGIFY(VK_FORMAT_A2B10G10R10_SSCALED_PACK32);
			STRINGIFY(VK_FORMAT_A2B10G10R10_UINT_PACK32);
			STRINGIFY(VK_FORMAT_A2B10G10R10_SINT_PACK32);
			STRINGIFY(VK_FORMAT_R16_UNORM);
			STRINGIFY(VK_FORMAT_R16_SNORM);
			STRINGIFY(VK_FORMAT_R16_USCALED);
			STRINGIFY(VK_FORMAT_R16_SSCALED);
			STRINGIFY(VK_FORMAT_R16_UINT);
			STRINGIFY(VK_FORMAT_R16_SINT);
			STRINGIFY(VK_FORMAT_R16_SFLOAT);
			STRINGIFY(VK_FORMAT_R16G16_UNORM);
			STRINGIFY(VK_FORMAT_R16G16_SNORM);
			STRINGIFY(VK_FORMAT_R16G16_USCALED);
			STRINGIFY(VK_FORMAT_R16G16_SSCALED);
			STRINGIFY(VK_FORMAT_R16G16_UINT);
			STRINGIFY(VK_FORMAT_R16G16_SINT);
			STRINGIFY(VK_FORMAT_R16G16_SFLOAT);
			STRINGIFY(VK_FORMAT_R16G16B16_UNORM);
			STRINGIFY(VK_FORMAT_R16G16B16_SNORM);
			STRINGIFY(VK_FORMAT_R16G16B16_USCALED);
			STRINGIFY(VK_FORMAT_R16G16B16_SSCALED);
			STRINGIFY(VK_FORMAT_R16G16B16_UINT);
			STRINGIFY(VK_FORMAT_R16G16B16_SINT);
			STRINGIFY(VK_FORMAT_R16G16B16_SFLOAT);
			STRINGIFY(VK_FORMAT_R16G16B16A16_UNORM);
			STRINGIFY(VK_FORMAT_R16G16B16A16_SNORM);
			STRINGIFY(VK_FORMAT_R16G16B16A16_USCALED);
			STRINGIFY(VK_FORMAT_R16G16B16A16_SSCALED);
			STRINGIFY(VK_FORMAT_R16G16B16A16_UINT);
			STRINGIFY(VK_FORMAT_R16G16B16A16_SINT);
			STRINGIFY(VK_FORMAT_R16G16B16A16_SFLOAT);
			STRINGIFY(VK_FORMAT_R32_UINT);
			STRINGIFY(VK_FORMAT_R32_SINT);
			STRINGIFY(VK_FORMAT_R32_SFLOAT);
			STRINGIFY(VK_FORMAT_R32G32_UINT);
			STRINGIFY(VK_FORMAT_R32G32_SINT);
			STRINGIFY(VK_FORMAT_R32G32_SFLOAT);
			STRINGIFY(VK_FORMAT_R32G32B32_UINT);
			STRINGIFY(VK_FORMAT_R32G32B32_SINT);
			STRINGIFY(VK_FORMAT_R32G32B32_SFLOAT);
			STRINGIFY(VK_FORMAT_R32G32B32A32_UINT);
			STRINGIFY(VK_FORMAT_R32G32B32A32_SINT);
			STRINGIFY(VK_FORMAT_R32G32B32A32_SFLOAT);
			STRINGIFY(VK_FORMAT_R64_UINT);
			STRINGIFY(VK_FORMAT_R64_SINT);
			STRINGIFY(VK_FORMAT_R64_SFLOAT);
			STRINGIFY(VK_FORMAT_R64G64_UINT);
			STRINGIFY(VK_FORMAT_R64G64_SINT);
			STRINGIFY(VK_FORMAT_R64G64_SFLOAT);
			STRINGIFY(VK_FORMAT_R64G64B64_UINT);
			STRINGIFY(VK_FORMAT_R64G64B64_SINT);
			STRINGIFY(VK_FORMAT_R64G64B64_SFLOAT);
			STRINGIFY(VK_FORMAT_R64G64B64A64_UINT);
			STRINGIFY(VK_FORMAT_R64G64B64A64_SINT);
			STRINGIFY(VK_FORMAT_R64G64B64A64_SFLOAT);
			STRINGIFY(VK_FORMAT_B10G11R11_UFLOAT_PACK32);
			STRINGIFY(VK_FORMAT_E5B9G9R9_UFLOAT_PACK32);

			default: return "Unknown format";
		}

		#undef STRINGIFY

		return "Unknown format"; // To avoid warnings
	}
}
