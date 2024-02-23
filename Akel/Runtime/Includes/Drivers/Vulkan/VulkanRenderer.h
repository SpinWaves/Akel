// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2024
// Updated : 23/02/2024

#ifndef __AK_VULKAN_RENDERER__
#define __AK_VULKAN_RENDERER__

#include <Drivers/Vulkan/PreCompiled.h>
#include <Graphics/RHI/RHIRenderer.h>
#include <Drivers/Vulkan/VulkanAPIHandle.h>

namespace Ak
{
	class AK_VULKAN_API VulkanRenderer : public RHIRenderer
	{
		public:
			VulkanRenderer();

			inline VulkanAPIHandle& GetAPIHandle() override { return m_api_handle; }

			[[nodiscard]]
			const char* VerbaliseVkResult(VkResult result) const noexcept;

			~VulkanRenderer() override;

		private:
			VulkanAPIHandle m_api_handle;
	};
}

#endif
