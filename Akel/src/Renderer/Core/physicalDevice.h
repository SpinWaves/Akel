// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2022
// Updated : 30/03/2022

#ifndef __AK_VK_PHYSICAL_DEVICE__
#define __AK_VK_PHYSICAL_DEVICE__

#include <Akpch.h>

namespace Ak
{
	class Instance;

	class PhysicalDevice
	{
		public:
			explicit PhysicalDevice(const Instance* instance);

			inline operator const VkPhysicalDevice& () const { return _physicalDevice; }

			inline const VkPhysicalDevice& getPhysicalDevice() const noexcept { return _physicalDevice; }
			inline const VkPhysicalDeviceProperties& getProperties() const noexcept { return _properties; }
			inline const VkPhysicalDeviceFeatures& getFeatures() const noexcept { return _features; }
			inline const VkPhysicalDeviceMemoryProperties& getMemoryProperties() const noexcept { return _memoryProperties; }
			inline const VkSampleCountFlagBits& getMsaaSamples() const noexcept { return _msaaSamples; }

		private:
			VkPhysicalDevice choosePhysicalDevice(const std::vector<VkPhysicalDevice>& devices);
			static uint32_t scorePhysicalDevice(const VkPhysicalDevice& device);
			VkSampleCountFlagBits getMaxUsableSampleCount() const;

			const Instance* _instance;

			VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
			VkPhysicalDeviceProperties _properties = {};
			VkPhysicalDeviceFeatures _features = {};
			VkPhysicalDeviceMemoryProperties _memoryProperties = {};
			VkSampleCountFlagBits _msaaSamples = VK_SAMPLE_COUNT_1_BIT;
	};
}

#endif // __AK_VK_PHYSICAL_DEVICE__
