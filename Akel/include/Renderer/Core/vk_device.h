// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 19/11/2023

#ifndef __AK_VK_DEVICE__
#define __AK_VK_DEVICE__

#include <Akpch.h>

namespace Ak
{
	class Device
	{
		public:
			void init();
			void destroy() noexcept;

			inline VkDevice& operator()() noexcept { return _device; }
			inline VkDevice& get() noexcept { return _device; }

			inline VkPhysicalDevice& getPhysicalDevice() noexcept { return _physicalDevice; }

		private:
			void pickPhysicalDevice();
			int deviceScore(VkPhysicalDevice device, VkSurfaceKHR surface);
			bool checkDeviceExtensionSupport(VkPhysicalDevice device);

		private:
			VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
			VkDevice _device = VK_NULL_HANDLE;
	};
}

#endif // __AK_VK_DEVICE__
