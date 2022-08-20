// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 20/08/2022

#include "render_core.h"
#include <Core/core.h>
#include <Utils/assert.h>

namespace Ak
{
	const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

	void Device::init()
	{
		pickPhysicalDevice();

		Queues::QueueFamilyIndices indices = Render_Core::get().getQueue().findQueueFamilies(_physicalDevice);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		float queuePriority = 1.0f;
		for(uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();

		createInfo.pEnabledFeatures = &deviceFeatures;

		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if(enableValidationLayers && !Core::ProjectFile::getBoolValue("vk_force_disable_validation_layers"))
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
			createInfo.enabledLayerCount = 0;

		if(vkCreateDevice(_physicalDevice, &createInfo, nullptr, &_device) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create logcal device");
	}

	void Device::pickPhysicalDevice()
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(Render_Core::get().getInstance().get(), &deviceCount, nullptr);

		if(deviceCount == 0)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to find GPUs with Vulkan support");

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(Render_Core::get().getInstance().get(), &deviceCount, devices.data());

		for(const auto& device : devices)
		{
			if(isDeviceSuitable(device))
			{
				_physicalDevice = device;
				break;
			}
		}

		if(_physicalDevice == VK_NULL_HANDLE)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to find a suitable GPU");
	}
	bool Device::isDeviceSuitable(VkPhysicalDevice device)
	{
		Queues::QueueFamilyIndices indices = Render_Core::get().getQueue().findQueueFamilies(device);

		bool extensionsSupported = checkDeviceExtensionSupport(device);

		bool swapChainAdequate = false;
		if(extensionsSupported)
		{
			SwapChain::SwapChainSupportDetails swapChainSupport = Render_Core::get().getSwapChain().querySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		return indices.isComplete() && extensionsSupported && swapChainAdequate;
	}
	bool Device::checkDeviceExtensionSupport(VkPhysicalDevice device)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for(const auto& extension : availableExtensions)
			requiredExtensions.erase(extension.extensionName);

		return requiredExtensions.empty();
	}

	void Device::destroy() noexcept
	{
		Ak_assert(_device != VK_NULL_HANDLE, "trying to destroy an uninit device");
		vkDestroyDevice(_device, nullptr);
	}
}
