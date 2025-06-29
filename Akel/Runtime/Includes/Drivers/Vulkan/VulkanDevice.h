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
			VulkanDevice(class VulkanInstance& instance, SharedPtr<class VulkanAdapter> adapter);

			SharedPtr<class RHIBuffer> CreateBuffer(BufferDescription description) override;
			SharedPtr<class RHITexture> CreateTexture(TextureDescription description) override;
			SharedPtr<class RHISwapchain> CreateSwapchain(SharedPtr<class RHISurface> surface, Vec2ui extent, bool vsync, bool priorise_srgb) noexcept override;
			SharedPtr<class RHIGraphicPipeline> CreateGraphicPipeline(GraphicPipelineDescription description) noexcept override;
			SharedPtr<class RHICommandEncoder> CreateCommandBuffer() noexcept override;
			SharedPtr<class RHICommandBuffer> CreateCommandBuffer(class RHICommandEncoder& encoder) noexcept override;

			void WaitForIdle() override;

			inline VkDevice Get() const noexcept { return m_device; }
			inline class VulkanInstance& GetInstance() const noexcept { return m_instance; }
			inline SharedPtr<class VulkanAdapter> GetAdapter() const noexcept { return p_adapter; }

			#define AK_VULKAN_DEVICE_FUNCTION(fn) PFN_##fn fn = nullptr;
				#include <Drivers/Vulkan/VulkanDevicePrototypes.h>
			#undef AK_VULKAN_DEVICE_FUNCTION

			~VulkanDevice() override;

		private:
			SharedPtr<class VulkanAdapter> p_adapter;
			class VulkanInstance& m_instance;
			VkDevice m_device = VK_NULL_HANDLE;
	};
}

#endif
