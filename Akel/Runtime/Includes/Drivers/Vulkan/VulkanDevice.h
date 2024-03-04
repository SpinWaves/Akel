// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/03/2024
// Updated : 04/03/2024

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
	};
}

#endif
