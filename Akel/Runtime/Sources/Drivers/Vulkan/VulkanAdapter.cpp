// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/Vulkan/VulkanAdapter.h>
#include <Drivers/Vulkan/VulkanInstance.h>
#include <Drivers/Vulkan/VulkanDevice.h>
#include <Graphics/RHI/RHIDevice.h>

namespace Ak
{
	[[nodiscard]] std::vector<VulkanPhysicalDeviceVendorID> ConvertAdapterVendorsToVulkanPhysicalDeviceVendorIDs(AdapterVendors vendors) noexcept
	{
		std::vector<VulkanPhysicalDeviceVendorID> ids;
		if((vendors & AdapterVendorAny) == 1)
		{
			ids.push_back(VulkanPhysicalDeviceVendorID::Unknown);
			return ids;
		}

		#undef VENDOR_FLAG
		#define VENDOR_FLAG(vendor) \
			if((vendors & AdapterVendor##vendor) == 1) \
				ids.push_back(VulkanPhysicalDeviceVendorID::vendor);

		VENDOR_FLAG(Amd);
		VENDOR_FLAG(Mesa);
		VENDOR_FLAG(ImgTec);
		VENDOR_FLAG(Nvidia);
		VENDOR_FLAG(Arm);
		VENDOR_FLAG(Broadcom);
		VENDOR_FLAG(Qualcomm);
		VENDOR_FLAG(Intel);
		VENDOR_FLAG(SamsungAMD);
		VENDOR_FLAG(Microsoft);

		#undef VENDOR_FLAG
		return ids;
	}

	VulkanAdapter::VulkanAdapter(VulkanInstance& instance, VkPhysicalDevice device) : m_device(device), m_instance(instance)
	{
		m_instance.vkGetPhysicalDeviceProperties(m_device, &m_properties);
		m_instance.vkGetPhysicalDeviceMemoryProperties(m_device, &m_memory_properties);

		DebugLog("Vulkan: picked adapter %", m_properties.deviceName);
	}

	SharedPtr<RHIDevice> VulkanAdapter::CreateDevice()
	{
		return nullptr;
	}
}
