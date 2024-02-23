// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/02/2024
// Updated : 23/02/2024

#ifndef __AK_VULKAN_API_HANDLE__
#define __AK_VULKAN_API_HANDLE__

#include <Drivers/Vulkan/PreCompiled.h>
#include <Graphics/RHI/RHIAPIHandle.h>

namespace Ak
{
	class AK_VULKAN_API VulkanAPIHandle : public RHIAPIHandle
	{
		public:
			VulkanAPIHandle();

			inline VkInstance Get() const noexcept { return m_instance; }
			inline VkInstance operator()() const noexcept { return m_instance; }

			~VulkanAPIHandle() override;

		private:
			VkInstance m_instance = VK_NULL_HANDLE;
	};
}

#endif
