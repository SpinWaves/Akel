// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/Vulkan/VulkanDevice.h>
#include <Drivers/Vulkan/VulkanInstance.h>

namespace Ak
{
	VulkanDevice::VulkanDevice(VulkanInstance& instance)
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
