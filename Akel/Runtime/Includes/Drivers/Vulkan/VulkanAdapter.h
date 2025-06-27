// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_VULKAN_ADAPTER_H
#define AK_VULKAN_ADAPTER_H

#include <Drivers/Vulkan/PreCompiled.h>
#include <Graphics/RHI/RHIAdapter.h>
#include <Drivers/Vulkan/Enums.h>
#include <Graphics/RHI/Defs.h>

namespace Ak
{
	[[nodiscard]] std::vector<VulkanPhysicalDeviceVendorID> ConvertAdapterVendorsToVulkanPhysicalDeviceVendorIDs(AdapterVendors vendors) noexcept;

	class AK_VULKAN_API VulkanAdapter : public RHIAdapter
	{
		public:
			VulkanAdapter(class VulkanInstance& instance, VkPhysicalDevice device);

			SharedPtr<class RHIDevice> CreateDevice() override;

			~VulkanAdapter() override = default;

		private:
			VkPhysicalDeviceProperties m_properties;
			VkPhysicalDeviceMemoryProperties m_memory_properties;
			VkPhysicalDevice m_device = VK_NULL_HANDLE;
			class VulkanInstance& m_instance;
	};
}

#endif
