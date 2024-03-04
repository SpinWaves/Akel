// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2024
// Updated : 04/03/2024

#ifndef __AK_VULKAN_RENDERER__
#define __AK_VULKAN_RENDERER__

#include <Drivers/Vulkan/PreCompiled.h>
#include <Graphics/RHI/RHIRenderer.h>
#include <Drivers/Vulkan/VulkanAPIHandle.h>
#include <Drivers/Vulkan/VulkanDevice.h>
#include <Core/Memory/UniquePtr.h>

namespace Ak
{
	[[nodiscard]]
	const char* VerbaliseVkResult(VkResult result) noexcept;

	class AK_VULKAN_API VulkanRenderer : public RHIRenderer
	{
		public:
			VulkanRenderer();

			inline VulkanAPIHandle& GetAPIHandle() override { return *m_api_handle; }
			inline VulkanDevice& GetDevice() override { return *m_device; }

			~VulkanRenderer() override;

		private:
			UniquePtr<VulkanAPIHandle> m_api_handle;
			UniquePtr<VulkanDevice> m_device;
	};
}

#endif
