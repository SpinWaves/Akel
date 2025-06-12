// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include "Drivers/Vulkan/Enums.h"
#include <Drivers/Vulkan/VulkanDevice.h>
#include <Drivers/Vulkan/VulkanRenderer.h>

namespace Ak
{
	[[nodiscard]]
	std::vector<VulkanPhysicalDeviceVendorID> ConvertPhysicalDeviceVendorsToVulkanPhysicalDeviceVendorIDs(PhysicalDeviceVendors vendors) noexcept
	{
		std::vector<VulkanPhysicalDeviceVendorID> ids;
		if((vendors & PhysicalDeviceVendorAny) == 1)
		{
			ids.push_back(VulkanPhysicalDeviceVendorID::Unknown);
			return ids;
		}

		#undef VENDOR_FLAG
		#define VENDOR_FLAG(vendor) \
			if((vendors & PhysicalDeviceVendor##vendor) == 1) \
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

	VulkanDevice::VulkanDevice(const PhysicalDeviceMinimalSpecs& specs) : RHIDevice()
	{
		VkPhysicalDevice physical_device = ChoosePhysicalDevice(specs);
		Verify(physical_device != VK_NULL_HANDLE, "Vulkan: could not find a physical device matching given minimal specs");

		VulkanInstance& instance = VulkanRenderer::Get().GetInstance();

		m_physical_device = physical_device;
		instance.vkGetPhysicalDeviceProperties(m_physical_device, &m_properties);
		instance.vkGetPhysicalDeviceMemoryProperties(m_physical_device, &m_memory_properties);

		DebugLog("Vulkan: device created from %", m_properties.deviceName);
	}

	NonOwningPtr<class RHIBuffer> VulkanDevice::CreateBuffer(BufferDescription description)
	{
		return nullptr;
	}

	NonOwningPtr<class RHITexture> VulkanDevice::CreateTexture(TextureDescription description)
	{
		return nullptr;
	}

	NonOwningPtr<class RHIRenderSurface> VulkanDevice::CreateRenderSurface() noexcept
	{
		return nullptr;
	}

	NonOwningPtr<class RHIGraphicPipeline> VulkanDevice::CreateGraphicPipeline() noexcept
	{
		return nullptr;
	}

	void VulkanDevice::WaitForIdle()
	{
		vkDeviceWaitIdle(m_device);
	}

	VkPhysicalDevice VulkanDevice::ChoosePhysicalDevice(const PhysicalDeviceMinimalSpecs& specs) noexcept
	{
		std::uint32_t count;
		VulkanInstance& instance = VulkanRenderer::Get().GetInstance();
		instance.vkEnumeratePhysicalDevices(instance, &count, nullptr);
		std::vector<VkPhysicalDevice> devices(count);
		instance.vkEnumeratePhysicalDevices(instance, &count, devices.data());

		std::array type_order{
			VK_PHYSICAL_DEVICE_TYPE_OTHER,
			VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU,
			VK_PHYSICAL_DEVICE_TYPE_CPU,
			VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,
			VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
		};

		if(count > 1)
		{
			std::sort(devices.begin(), devices.end(), [instance, &type_order](VkPhysicalDevice lhs, VkPhysicalDevice rhs)
			{
				VkPhysicalDeviceProperties lhs_properties;
				instance.vkGetPhysicalDeviceProperties(lhs, &lhs_properties);
				VkPhysicalDeviceProperties rhs_properties;
				instance.vkGetPhysicalDeviceProperties(rhs, &rhs_properties);

				VkPhysicalDeviceMemoryProperties lhs_memory_properties;
				instance.vkGetPhysicalDeviceMemoryProperties(lhs, &lhs_memory_properties);
				VkPhysicalDeviceMemoryProperties rhs_memory_properties;
				instance.vkGetPhysicalDeviceMemoryProperties(rhs, &rhs_memory_properties);

				if(type_order[lhs_properties.deviceType] == type_order[rhs_properties.deviceType])
					return lhs_memory_properties.memoryHeaps[0].size > rhs_memory_properties.memoryHeaps[0].size;
				return type_order[lhs_properties.deviceType] > type_order[rhs_properties.deviceType];
			});
		}

		for(auto device : devices)
		{
			VkPhysicalDeviceProperties properties;
			instance.vkGetPhysicalDeviceProperties(device, &properties);
			VkPhysicalDeviceMemoryProperties memory_properties;
			instance.vkGetPhysicalDeviceMemoryProperties(device, &memory_properties);

			std::uint64_t memory = static_cast<uint64_t>(memory_properties.memoryHeaps[0].size);
			std::uint32_t memory_mb = static_cast<uint32_t>(memory / 1024 / 1024);

			if(specs.type != PhysicalDeviceType::Any)
			{
				switch(specs.type)
				{
					case PhysicalDeviceType::Other:
					{
						if(properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_OTHER)
							continue;
					}
					case PhysicalDeviceType::CPU:
					{
						if(properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_CPU)
							continue;
					}
					case PhysicalDeviceType::Virtual:
					{
						if(properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU)
							continue;
					}
					case PhysicalDeviceType::Integrated:
					{
						if(properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
							continue;
					}
					case PhysicalDeviceType::Discrete:
					{
						if(properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
							continue;
					}

					default : break;
				}
			}

			if(specs.vendors != PhysicalDeviceVendorAny)
			{
				auto ids = ConvertPhysicalDeviceVendorsToVulkanPhysicalDeviceVendorIDs(specs.vendors);
				auto it = std::find_if(ids.begin(), ids.end(), [properties](VulkanPhysicalDeviceVendorID id)
				{
					return static_cast<std::uint32_t>(id) == properties.vendorID;
				});
				if(it == ids.end())
					continue;
			}

			if(memory_mb < specs.memory)
				continue;

			return device;
		}

		return VK_NULL_HANDLE;
	}

	VulkanDevice::~VulkanDevice()
	{
		vkDestroyDevice(m_device, nullptr);
		DebugLog("Vulkan: device destroyed");
	}
}
