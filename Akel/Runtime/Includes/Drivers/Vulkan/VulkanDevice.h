// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_VULKAN_DEVICE__
#define __AK_VULKAN_DEVICE__

#include <Drivers/Vulkan/PreCompiled.h>
#include <Drivers/Vulkan/Enums.h>
#include <Graphics/RHI/RHIDevice.h>
#include <Graphics/RHI/Defs.h>

namespace Ak
{
	[[nodiscard]]
	std::vector<VulkanPhysicalDeviceVendorID> ConvertPhysicalDeviceVendorsToVulkanPhysicalDeviceVendorIDs(PhysicalDeviceVendors vendors) noexcept;

	class AK_VULKAN_API VulkanDevice : public RHIDevice
	{
		public:
			VulkanDevice(const PhysicalDeviceMinimalSpecs& specs);

			NonOwningPtr<class RHIBuffer> CreateBuffer(BufferDescription description) override;
			NonOwningPtr<class RHITexture> CreateTexture(TextureDescription description) override;
			NonOwningPtr<class RHIRenderSurface> CreateRenderSurface() noexcept override;
			NonOwningPtr<class RHIGraphicPipeline> CreateGraphicPipeline() noexcept override;

			void WaitForIdle() override;

			inline operator VkDevice() const noexcept { return m_device; }
			inline VkPhysicalDevice GetPhysicalDevice() const noexcept { return m_physical_device; }

			#define AK_VULKAN_DEVICE_FUNCTION(fn) PFN_##fn fn = nullptr;
				#include <Drivers/Vulkan/VulkanDevicePrototypes.h>
			#undef AK_VULKAN_DEVICE_FUNCTION

			~VulkanDevice() override;

		private:
			VkPhysicalDevice ChoosePhysicalDevice(const PhysicalDeviceMinimalSpecs& specs) noexcept;

		private:
			VkDevice m_device = VK_NULL_HANDLE;
			VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
			VkPhysicalDeviceProperties m_properties;
			VkPhysicalDeviceMemoryProperties m_memory_properties;
	};
}

#endif
