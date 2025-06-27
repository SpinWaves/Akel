// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_VULKAN_DEVICE_H
#define AK_VULKAN_DEVICE_H

#include <Drivers/Vulkan/PreCompiled.h>
#include <Drivers/Vulkan/Enums.h>
#include <Graphics/RHI/RHIDevice.h>
#include <Graphics/RHI/Defs.h>

namespace Ak
{
	class AK_VULKAN_API VulkanDevice : public RHIDevice
	{
		public:
			VulkanDevice(class RHIInstance& instance, SharedPtr<class RHIAdapter> adapter);

			SharedPtr<class RHIBuffer> CreateBuffer(BufferDescription description) override;
			SharedPtr<class RHITexture> CreateTexture(TextureDescription description) override;
			SharedPtr<class RHISurface> CreateSurface() noexcept override;
			SharedPtr<class RHIGraphicPipeline> CreateGraphicPipeline(GraphicPipelineDescription description) noexcept override;
			SharedPtr<class RHICommandEncoder> CreateCommandBuffer() noexcept override;
			SharedPtr<class RHICommandBuffer> CreateCommandBuffer(class RHICommandEncoder& encoder) noexcept override;

			void WaitForIdle() override;

			inline operator VkDevice() const noexcept { return m_device; }

			#define AK_VULKAN_DEVICE_FUNCTION(fn) PFN_##fn fn = nullptr;
				#include <Drivers/Vulkan/VulkanDevicePrototypes.h>
			#undef AK_VULKAN_DEVICE_FUNCTION

			~VulkanDevice() override;

		private:
			VkDevice m_device = VK_NULL_HANDLE;
	};
}

#endif
