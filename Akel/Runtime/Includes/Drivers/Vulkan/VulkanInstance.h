// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/02/2024
// Updated : 10/04/2024

#ifndef __AK_VULKAN_INSTANCE__
#define __AK_VULKAN_INSTANCE__

#include <Drivers/Vulkan/PreCompiled.h>

namespace Ak
{
	class AK_VULKAN_API VulkanInstance
	{
		public:
			VulkanInstance();

			inline bool IsInit() const noexcept { return m_instance != VK_NULL_HANDLE; }
			inline VkInstance Get() const noexcept { return m_instance; }
			inline VkInstance operator()() const noexcept { return m_instance; }

			~VulkanInstance();

		private:
			VkInstance m_instance = VK_NULL_HANDLE;
	};
}

#endif
