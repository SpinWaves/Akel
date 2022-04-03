// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 03/04/2022

#ifndef __AK_VK_DEVICE__
#define __AK_VK_DEVICE__

#include <Akpch.h>

namespace Ak
{
	class Device
	{
		public:
			void init();
			inline void destroy() noexcept { vkDestroyDevice(_device, nullptr); }

			inline VkDevice& operator()() const noexcept { return _device; }
			inline VkDevice& get() const noexcept { return _device; }

			inline VkPhysicalDevice& getPhysicalDevice() const noexcept { return _physicalDevice; }
			
		private:
			void pickPhysicalDevice();
			bool isDeviceSuitable(VkPhysicalDevice device);
			bool checkDeviceExtensionSupport(VkPhysicalDevice device);

			VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
			VkDevice _device = VK_NULL_HANDLE;
	};
}

#endif // __AK_VK_DEVICE__
