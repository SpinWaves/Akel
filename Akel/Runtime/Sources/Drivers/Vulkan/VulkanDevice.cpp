// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/03/2024
// Updated : 04/03/2024

#include <Drivers/Vulkan/VulkanDevice.h>

namespace Ak
{
	VulkanDevice::VulkanDevice()
	{

	}

	NonOwningPtr<class RHIBuffer> VulkanDevice::CreateBuffer(BufferDescription description)
	{
	}

	NonOwningPtr<class RHITexture> VulkanDevice::CreateTexture(TextureDescription description)
	{
	}

	NonOwningPtr<class RHIRenderSurface> VulkanDevice::CreateRenderSurface() noexcept
	{
	}

	NonOwningPtr<class RHIGraphicPipeline> VulkanDevice::CreateGraphicPipeline() noexcept
	{
	}

	void VulkanDevice::WaitForIdle()
	{
	}

	VulkanDevice::~VulkanDevice()
	{
	}
}
