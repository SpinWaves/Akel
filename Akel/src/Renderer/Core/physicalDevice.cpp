// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2022
// Updated : 28/03/2022

#include "physicalDevice.h"
#include "instance.h"

namespace Ak
{
	static const std::vector<VkSampleCountFlagBits> STAGE_FLAG_BITS = { VK_SAMPLE_COUNT_64_BIT, VK_SAMPLE_COUNT_32_BIT, VK_SAMPLE_COUNT_16_BIT, VK_SAMPLE_COUNT_8_BIT, VK_SAMPLE_COUNT_4_BIT, VK_SAMPLE_COUNT_2_BIT };

	PhysicalDevice::PhysicalDevice(const Instance* instance) : _instance(instance)
	{
		uint32_t physicalDeviceCount = 0;
		vkEnumeratePhysicalDevices(*_instance, &physicalDeviceCount, nullptr);
		std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
		vkEnumeratePhysicalDevices(*_instance, &physicalDeviceCount, physicalDevices.data());

		_physicalDevice = choosePhysicalDevice(physicalDevices);
		if(!physicalDevice)
			Core::log::report(FATAL_ERROR, "vulkan runtime error, failed to find a suitable GPU");

		vkGetPhysicalDeviceProperties(_physicalDevice, &_properties);
		vkGetPhysicalDeviceFeatures(_physicalDevice, &_features);
		vkGetPhysicalDeviceMemoryProperties(_physicalDevice, &_memoryProperties);
		_msaaSamples = getMaxUsableSampleCount();
	}

	VkPhysicalDevice PhysicalDevice::choosePhysicalDevice(const std::vector<VkPhysicalDevice>& devices)
	{
		std::multimap<uint32_t, VkPhysicalDevice> rankedDevices;

		for(const auto &device : devices)
			rankedDevices.emplace(scorePhysicalDevice(device), device);
		if(rankedDevices.rbegin()->first > 0)
			return rankedDevices.rbegin()->second;

		return nullptr;
	}

	uint32_t PhysicalDevice::scorePhysicalDevice(const VkPhysicalDevice &device)
	{
		uint32_t score = 0;

		uint32_t extensionPropertyCount = 0;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionPropertyCount, nullptr);
		std::vector<VkExtensionProperties> extensionProperties(extensionPropertyCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionPropertyCount, extensionProperties.data());

		for(const char *currentExtension : LogicalDevice::DeviceExtensions)
		{
			bool extensionFound = false;

			for(const auto &extension : extensionProperties)
			{
				if(strcmp(currentExtension, extension.extensionName) == 0)
				{
					extensionFound = true;
					break;
				}
			}

			if(!extensionFound)
				return 0;
		}

		VkPhysicalDeviceProperties physicalDeviceProperties;
		VkPhysicalDeviceFeatures physicalDeviceFeatures;
		vkGetPhysicalDeviceProperties(_device, &physicalDeviceProperties);
		vkGetPhysicalDeviceFeatures(_device, &physicalDeviceFeatures);

		if(physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			score += 1000;

		score += physicalDeviceProperties.limits.maxImageDimension2D;
		return score;
	}

	VkSampleCountFlagBits PhysicalDevice::getMaxUsableSampleCount() const
	{
		VkPhysicalDeviceProperties physicalDeviceProperties;
		vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

		auto counts = std::min(physicalDeviceProperties.limits.framebufferColorSampleCounts, physicalDeviceProperties.limits.framebufferDepthSampleCounts);

		for(const auto &sampleFlag : STAGE_FLAG_BITS)
		{
			if(counts & sampleFlag)
				return sampleFlag;
		}

		return VK_SAMPLE_COUNT_1_BIT;
	}
}
