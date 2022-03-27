// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2022
// Updated : 27/03/2022

#include "render_core.h"
#include <Core/core.h>

namespace Ak
{
	const std::vector<const char*> LogicalDevice::deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME}; // VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME

	LogicalDevice::LogicalDevice(const Instance *instance, const PhysicalDevice *physicalDevice, const Surface *surface) : _instance(instance), _physicalDevice(physicalDevice), _surface(surface)
	{
		createQueueIndices();
		createLogicalDevice();
	}

	void LogicalDevice::createQueueIndices()
	{
		uint32_t deviceQueueFamilyPropertyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(*_physicalDevice, &deviceQueueFamilyPropertyCount, nullptr);
		std::vector<VkQueueFamilyProperties> deviceQueueFamilyProperties(deviceQueueFamilyPropertyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(*_physicalDevice, &deviceQueueFamilyPropertyCount, deviceQueueFamilyProperties.data());

		std::optional<uint32_t> graphicsFamily, presentFamily, computeFamily, transferFamily;

		for(uint32_t i = 0; i < deviceQueueFamilyPropertyCount; i++)
		{
			// Check for graphics support.
			if(deviceQueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				graphicsFamily = i;
				_graphicsFamily = i;
				supportedQueues |= VK_QUEUE_GRAPHICS_BIT;
			}

			// Check for presentation support.
			VkBool32 presentSupport;
			vkGetPhysicalDeviceSurfaceSupportKHR(*_physicalDevice, i, *_surface, &presentSupport);

			if(deviceQueueFamilyProperties[i].queueCount > 0 && presentSupport)
			{
				presentFamily = i;
				_presentFamily = i;
			}

			// Check for compute support.
			if(deviceQueueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
			{
				computeFamily = i;
				_computeFamily = i;
				supportedQueues |= VK_QUEUE_COMPUTE_BIT;
			}

			// Check for transfer support.
			if(deviceQueueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
			{
				transferFamily = i;
				_transferFamily = i;
				supportedQueues |= VK_QUEUE_TRANSFER_BIT;
			}

			if(graphicsFamily && presentFamily && computeFamily && transferFamily)
				break;
		}

		if(!graphicsFamily)
			Core::log::report(FATAL_ERROR, "failed to find queue family supporting VK_QUEUE_GRAPHICS_BIT");
	}

	void LogicalDevice::createLogicalDevice()
	{
		auto physicalDeviceFeatures = physicalDevice->getFeatures();

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		float queuePriorities[1] = { 0.0f };

		if(supportedQueues & VK_QUEUE_GRAPHICS_BIT)
		{
			VkDeviceQueueCreateInfo graphicsQueueCreateInfo{};
			graphicsQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			graphicsQueueCreateInfo.queueFamilyIndex = _graphicsFamily;
			graphicsQueueCreateInfo.queueCount = 1;
			graphicsQueueCreateInfo.pQueuePriorities = queuePriorities;
			queueCreateInfos.emplace_back(graphicsQueueCreateInfo);
		}
		else
			_graphicsFamily = 0; // VK_NULL_HANDLE;

		if(supportedQueues & VK_QUEUE_COMPUTE_BIT && computeFamily != _graphicsFamily)
		{
			VkDeviceQueueCreateInfo computeQueueCreateInfo{};
			computeQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			computeQueueCreateInfo.queueFamilyIndex = _computeFamily;
			computeQueueCreateInfo.queueCount = 1;
			computeQueueCreateInfo.pQueuePriorities = queuePriorities;
			queueCreateInfos.emplace_back(computeQueueCreateInfo);
		}
		else
			_computeFamily = _graphicsFamily;

		if(supportedQueues & VK_QUEUE_TRANSFER_BIT && _transferFamily != _graphicsFamily && _transferFamily != _computeFamily)
		{
			VkDeviceQueueCreateInfo transferQueueCreateInfo{};
			transferQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			transferQueueCreateInfo.queueFamilyIndex = _transferFamily;
			transferQueueCreateInfo.queueCount = 1;
			transferQueueCreateInfo.pQueuePriorities = queuePriorities;
			queueCreateInfos.emplace_back(transferQueueCreateInfo);
		}
		else
			_transferFamily = _graphicsFamily;

		// Enable sample rate shading filtering if supported.
		if(physicalDeviceFeatures.sampleRateShading)
			_enabledFeatures.sampleRateShading = VK_TRUE;

		// Fill mode non solid is required for wireframe display.
		if(physicalDeviceFeatures.fillModeNonSolid)
		{
			_enabledFeatures.fillModeNonSolid = VK_TRUE;

			// Wide lines must be present for line width > 1.0f.
			if(physicalDeviceFeatures.wideLines)
				_enabledFeatures.wideLines = VK_TRUE;
		} 
		else
			Core::log::report(WARNING, "selected GPU does not support wireframe pipelines");

		if(physicalDeviceFeatures.samplerAnisotropy)
			_enabledFeatures.samplerAnisotropy = VK_TRUE;
		else
			Core::log::report(WARNING, "selected GPU does not support sampler anisotropy");

		if(physicalDeviceFeatures.textureCompressionBC)
			_enabledFeatures.textureCompressionBC = VK_TRUE;
		else if(physicalDeviceFeatures.textureCompressionASTC_LDR)
			_enabledFeatures.textureCompressionASTC_LDR = VK_TRUE;
		else if(physicalDeviceFeatures.textureCompressionETC2)
			_enabledFeatures.textureCompressionETC2 = VK_TRUE;

		if(physicalDeviceFeatures.vertexPipelineStoresAndAtomics)
			_enabledFeatures.vertexPipelineStoresAndAtomics = VK_TRUE;
		else
			Core::log::report(WARNING, "selected GPU does not support vertex pipeline stores and atomics");

		if(physicalDeviceFeatures.fragmentStoresAndAtomics)
			_enabledFeatures.fragmentStoresAndAtomics = VK_TRUE;
		else
			Core::log::report(WARNING "selected GPU does not support fragment stores and atomics");

		if(physicalDeviceFeatures.shaderStorageImageExtendedFormats)
			_enabledFeatures.shaderStorageImageExtendedFormats = VK_TRUE;
		else
			Core::log::report(WARNING, "selected GPU does not support shader storage extended formats");

		if(physicalDeviceFeatures.shaderStorageImageWriteWithoutFormat)
			_enabledFeatures.shaderStorageImageWriteWithoutFormat = VK_TRUE;
		else
			Core::log::report(WARNING, "selected GPU does not support shader storage write without format");

		//_enabledFeatures.shaderClipDistance = VK_TRUE;
		//_enabledFeatures.shaderCullDistance = VK_TRUE;

		if(physicalDeviceFeatures.geometryShader)
			_enabledFeatures.geometryShader = VK_TRUE;
		else
			Core::log::report(WARNING, "selected GPU does not support geometry shaders");

		if(physicalDeviceFeatures.tessellationShader)
			_enabledFeatures.tessellationShader = VK_TRUE;
		else
			Core::log::report(WARNING, "selected GPU does not support tessellation shaders");

		if(physicalDeviceFeatures.multiViewport)
			_enabledFeatures.multiViewport = VK_TRUE;
		else
			Core::log::report(WARNING, "selected GPU does not support multi viewports");

		VkDeviceCreateInfo deviceCreateInfo{};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		if(instance->getEnableValidationLayers())
		{
			deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(Instance::validationLayers.size());
			deviceCreateInfo.ppEnabledLayerNames = Instance::validationLayers.data();
		}
		deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(DeviceExtensions.size());
		deviceCreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();
		deviceCreateInfo.p_enabledFeatures = &_enabledFeatures;
		RCore::checkVk(vkCreateDevice(*_physicalDevice, &deviceCreateInfo, nullptr, &_logicalDevice));

		volkLoadDevice(_logicalDevice);

		vkGetDeviceQueue(_logicalDevice, _graphicsFamily, 0, &_graphicsQueue);
		vkGetDeviceQueue(_logicalDevice, _presentFamily,  0, &_presentQueue);
		vkGetDeviceQueue(_logicalDevice, _computeFamily,  0, &_computeQueue);
		vkGetDeviceQueue(_logicalDevice, _transferFamily, 0, &_transferQueue);
	}

	LogicalDevice::~LogicalDevice()
	{
		RCore::checkVk(vkDeviceWaitIdle(_logicalDevice));
		vkDestroyDevice(_logicalDevice, nullptr);
	}
}
