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
			SharedPtr<class RHICommandEncoder> CreateCommandEncoder() noexcept override;
			SharedPtr<class RHICommandBuffer> CreateCommandBuffer(class RHICommandEncoder& encoder) noexcept override;

			void WaitForIdle() override;

			AK_FORCEINLINE VkQueue GetTransferQueue() const noexcept { return m_transfer_queue; }
			AK_FORCEINLINE VkQueue GetGraphicsQueue() const noexcept { return m_graphics_queue; }
			AK_FORCEINLINE VkQueue GetComputeQueue() const noexcept { return m_compute_queue; }
			AK_FORCEINLINE VkQueue GetPresentQueue() const noexcept { return m_present_queue; }

			AK_FORCEINLINE std::uint32_t GetTransferQueueFamily() const noexcept { return *m_transfer_queue_family; }
			AK_FORCEINLINE std::uint32_t GetGraphicsQueueFamily() const noexcept { return *m_graphics_queue_family; }
			AK_FORCEINLINE std::uint32_t GetComputeQueueFamily() const noexcept { return *m_compute_queue_family; }
			AK_FORCEINLINE std::uint32_t GetPresentQueueFamily() const noexcept { return *m_present_queue_family; }

			AK_FORCEINLINE VkDevice Get() const noexcept { return m_device; }
			AK_FORCEINLINE class VulkanInstance& GetInstance() const noexcept { return m_instance; }
			inline SharedPtr<class VulkanAdapter> GetAdapter() const noexcept { return p_adapter; }

			#define AK_VULKAN_DEVICE_FUNCTION(fn) PFN_##fn fn = nullptr;
				#include <Drivers/Vulkan/VulkanDevicePrototypes.h>
			#undef AK_VULKAN_DEVICE_FUNCTION

			~VulkanDevice() override;

		private:
			bool FindQueueFamilies();

		private:
			SharedPtr<class VulkanAdapter> p_adapter;
			class VulkanInstance& m_instance;
			VkDevice m_device = VK_NULL_HANDLE;
			VkQueue m_transfer_queue = VK_NULL_HANDLE;
			VkQueue m_graphics_queue = VK_NULL_HANDLE;
			VkQueue m_compute_queue = VK_NULL_HANDLE;
			VkQueue m_present_queue = VK_NULL_HANDLE;
			std::optional<std::uint32_t> m_transfer_queue_family;
			std::optional<std::uint32_t> m_graphics_queue_family;
			std::optional<std::uint32_t> m_compute_queue_family;
			std::optional<std::uint32_t> m_present_queue_family;
	};
}

#endif
