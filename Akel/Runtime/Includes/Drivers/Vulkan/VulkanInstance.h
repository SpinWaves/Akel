// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

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
