// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/Vulkan/Enums.h>
#include <Drivers/Vulkan/VulkanDevice.h>
#include <Drivers/Vulkan/VulkanInstance.h>
#include <Drivers/Vulkan/VulkanSwapchain.h>
#include <Drivers/Vulkan/VulkanAdapter.h>

namespace Ak
{
	VulkanDevice::VulkanDevice(VulkanInstance& instance, SharedPtr<VulkanAdapter> adapter) : RHIDevice(instance, adapter), p_adapter(adapter), m_instance(instance)
	{
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

	SharedPtr<class RHICommandEncoder> VulkanDevice::CreateCommandBuffer() noexcept
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

	VulkanDevice::~VulkanDevice()
	{
		vkDestroyDevice(m_device, nullptr);
		DebugLog("Vulkan: device destroyed");
	}
}
