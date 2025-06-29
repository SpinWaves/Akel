// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_VULKAN_SWAPCHAIN_H
#define AK_VULKAN_SWAPCHAIN_H

#include <Drivers/Vulkan/PreCompiled.h>
#include <Graphics/RHI/RHISwapchain.h>

namespace Ak
{
	class AK_VULKAN_API VulkanSwapchain : public RHISwapchain
	{
		public:
			struct SwapchainSupportDetails
			{
				VkSurfaceCapabilitiesKHR capabilities;
				std::vector<VkSurfaceFormatKHR> formats;
				std::vector<VkPresentModeKHR> present_modes;
			};

		public:
			VulkanSwapchain(class VulkanDevice& device, SharedPtr<class VulkanSurface> surface, Vec2ui extent, bool vsync, bool priorise_srgb);

			AK_FORCEINLINE VkSwapchainKHR Get() const noexcept { return m_swapchain; }

			~VulkanSwapchain() override;

		private:
			SwapchainSupportDetails QuerySwapchainSupport(SharedPtr<class VulkanSurface> surface);

		private:
			class VulkanDevice& m_device;
			VkSwapchainKHR m_swapchain = VK_NULL_HANDLE;
	};
}

#endif
