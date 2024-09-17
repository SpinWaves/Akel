// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_VULKAN_DEVICE__
#define __AK_VULKAN_DEVICE__

#include <Drivers/Vulkan/PreCompiled.h>
#include <Graphics/RHI/RHIDevice.h>

namespace Ak
{
	class AK_VULKAN_API VulkanDevice : public RHIDevice
	{
		public:
			VulkanDevice();

			NonOwningPtr<class RHIBuffer> CreateBuffer(BufferDescription description) override;
			NonOwningPtr<class RHITexture> CreateTexture(TextureDescription description) override;
			NonOwningPtr<class RHIRenderSurface> CreateRenderSurface() noexcept override;
			NonOwningPtr<class RHIGraphicPipeline> CreateGraphicPipeline() noexcept override;

			void WaitForIdle() override;

			~VulkanDevice() override;

		private:
			VkDevice m_device = VK_NULL_HANDLE;
			VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
	};
}

#endif
