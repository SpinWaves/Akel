// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/Vulkan/Enums.h>
#include <Drivers/Vulkan/VulkanDevice.h>
#include <Drivers/Vulkan/VulkanInstance.h>
#include <Drivers/Vulkan/VulkanSwapchain.h>
#include <Drivers/Vulkan/VulkanAdapter.h>
#include <Drivers/Vulkan/VulkanSurface.h>
#include <Platform/PlatformModule.h>

namespace Ak
{
	VulkanDevice::VulkanDevice(VulkanInstance& instance, SharedPtr<VulkanAdapter> adapter) : RHIDevice(instance, adapter), p_adapter(adapter), m_instance(instance)
	{
		if(!FindQueueFamilies())
			FatalError("Vulkan: could not find all needed family queues");

		std::array extensions{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		VkPhysicalDeviceFeatures features{
			VK_FALSE
		};

		const float queue_priority = 1.0f;

		std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
		std::set<std::uint32_t> unique_families;

		auto add_queue_create_info = [&](std::optional<std::uint32_t>& family_index)
		{
			if(!family_index.has_value() || !unique_families.insert(*family_index).second)
				return;

			VkDeviceQueueCreateInfo info{};
			info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			info.queueFamilyIndex = *family_index;
			info.queueCount = 1;
			info.pQueuePriorities = &queue_priority;
			info.flags = 0;
			info.pNext = nullptr;

			queue_create_infos.push_back(info);
		};

		add_queue_create_info(m_graphics_queue_family);
		add_queue_create_info(m_transfer_queue_family);
		add_queue_create_info(m_compute_queue_family);
		add_queue_create_info(m_present_queue_family);

		VkDeviceCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		create_info.queueCreateInfoCount = queue_create_infos.size();
		create_info.pQueueCreateInfos = queue_create_infos.data();
		create_info.pEnabledFeatures = &features;
		create_info.enabledExtensionCount = extensions.size();
		create_info.ppEnabledExtensionNames = extensions.data();
		create_info.enabledLayerCount = 0;
		create_info.ppEnabledLayerNames = nullptr;
		create_info.flags = 0;
		create_info.pNext = nullptr;
		CheckVk(m_instance.vkCreateDevice(p_adapter->Get(), &create_info, nullptr, &m_device));

		m_instance.GetLoader().LoadDevice(*this);

		vkGetDeviceQueue(m_device, *m_graphics_queue_family, 0, &m_graphics_queue);
		vkGetDeviceQueue(m_device, *m_transfer_queue_family, 0, &m_transfer_queue);
		vkGetDeviceQueue(m_device, *m_compute_queue_family, 0, &m_compute_queue);
		vkGetDeviceQueue(m_device, *m_present_queue_family, 0, &m_present_queue);

		DebugLog("Vulkan: created device from adapter %", p_adapter->GetProperties().deviceName);
	}

	SharedPtr<class RHIBuffer> VulkanDevice::CreateBuffer(BufferDescription description)
	{
		return nullptr;
	}

	SharedPtr<class RHITexture> VulkanDevice::CreateTexture(TextureDescription description)
	{
		return nullptr;
	}

	SharedPtr<class RHISwapchain> VulkanDevice::CreateSwapchain(SharedPtr<class RHISurface> surface, Vec2ui extent, bool vsync, bool priorise_srgb) noexcept
	{
		return MakeShared<VulkanSwapchain>(*this, surface, extent, vsync, priorise_srgb);
	}

	SharedPtr<class RHIGraphicPipeline> VulkanDevice::CreateGraphicPipeline(GraphicPipelineDescription description) noexcept
	{
		return nullptr;
	}

	SharedPtr<class RHICommandEncoder> VulkanDevice::CreateCommandEncoder() noexcept
	{
		return nullptr;
	}

	SharedPtr<class RHICommandBuffer> VulkanDevice::CreateCommandBuffer(class RHICommandEncoder& encoder) noexcept
	{
		return nullptr;
	}

	void VulkanDevice::WaitForIdle()
	{
		vkDeviceWaitIdle(m_device);
	}

	bool VulkanDevice::FindQueueFamilies()
	{
		UniquePtr<class SIWindow> window = PlatformModule::Get().CreateDummyWindow();
		VulkanSurface surface(m_instance, window.Get());

		std::uint32_t families_count;
		m_instance.vkGetPhysicalDeviceQueueFamilyProperties(p_adapter->Get(), &families_count, nullptr);
		Verify(families_count != 0, "Vulkan: no queue family found");

		std::vector<VkQueueFamilyProperties> families(families_count);
		m_instance.vkGetPhysicalDeviceQueueFamilyProperties(p_adapter->Get(), &families_count, families.data());

		std::uint32_t i = 0;

		// Find dedicated queues
		for(const auto& family : families)
		{
			VkBool32 present_support = false;
			m_instance.vkGetPhysicalDeviceSurfaceSupportKHR(p_adapter->Get(), i, surface.Get(), &present_support);

			bool is_graphics = family.queueFlags & VK_QUEUE_GRAPHICS_BIT;
			bool is_compute = family.queueFlags & VK_QUEUE_COMPUTE_BIT;
			bool is_transfer = family.queueFlags & VK_QUEUE_TRANSFER_BIT;

			if(is_transfer && !(is_compute || is_graphics) && !m_transfer_queue_family.has_value())
				m_transfer_queue_family = i;
			if(is_compute && !is_graphics && !m_compute_queue_family.has_value())
				m_compute_queue_family = i;

			// Prefer graphics queue with present support
			if(is_graphics && present_support)
			{
				m_graphics_queue_family = i;
				m_present_queue_family = i;
			}

			if(present_support && !m_present_queue_family.has_value())
				m_present_queue_family = i;

			i++;
		}

		if(!m_compute_queue_family.has_value() || !m_graphics_queue_family.has_value() || !m_present_queue_family.has_value() || !m_transfer_queue_family.has_value())
		{
			// Fallback
			i = 0;
			for(const auto& family : families)
			{
				bool is_graphics = family.queueFlags & VK_QUEUE_GRAPHICS_BIT;
				bool is_compute = family.queueFlags & VK_QUEUE_COMPUTE_BIT;
				bool is_transfer = family.queueFlags & VK_QUEUE_TRANSFER_BIT;

				if(is_transfer && !m_transfer_queue_family.has_value())
					m_transfer_queue_family = i;
				if(is_compute && !m_compute_queue_family.has_value())
					m_compute_queue_family = i;
				if(is_graphics && !m_graphics_queue_family.has_value())
					m_graphics_queue_family = i;

				i++;
			}
		}

		return (m_compute_queue_family.has_value() && m_graphics_queue_family.has_value() && m_present_queue_family.has_value() && m_transfer_queue_family.has_value());
	}

	VulkanDevice::~VulkanDevice()
	{
		vkDestroyDevice(m_device, nullptr);
		DebugLog("Vulkan: device destroyed");
	}
}
