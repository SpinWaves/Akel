// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 16/10/2023

#include <Renderer/Core/render_core.h>
#include <Core/core.h>
#include <Utils/assert.h>

namespace Ak
{
	const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

	void Device::init()
	{
		pickPhysicalDevice();

		Queues::QueueFamilyIndices indices = Render_Core::get().getQueue().getFamilies();

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

        if(enableValidationLayers && !getMainAppProjectFile().archive()["vk_force_disable_validation_layers"])
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
			createInfo.enabledLayerCount = 0;

		if(vkCreateDevice(_physicalDevice, &createInfo, nullptr, &_device) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create logcal device");
		Core::log::report(DEBUGLOG, "Vulkan : created new logical device");
	}

	void Device::pickPhysicalDevice()
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(Render_Core::get().getInstance().get(), &deviceCount, nullptr);

		if(deviceCount == 0)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to find GPU with Vulkan support");

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(Render_Core::get().getInstance().get(), &deviceCount, devices.data());

		Core::ProjectFile& project = getMainAppProjectFile();
		int saved_index = -1;
		if(project.archive()["render_core"].contains("physical_device"))
		{
			saved_index = project.archive()["render_core"]["physical_device"];
			if(saved_index < devices.size())
				_physicalDevice = devices[saved_index];
		}

		if(project.archive()["render_core"].contains("queue_families"))
		{
			if(project.archive()["render_core"]["queue_families"].contains("graphics") && project.archive()["render_core"]["queue_families"].contains("present"))
			{
				Render_Core::get().getQueue()._families = Queues::QueueFamilyIndices{};
				Render_Core::get().getQueue()._families->graphicsFamily.emplace(project.archive()["render_core"]["queue_families"]["graphics"]);
				Render_Core::get().getQueue()._families->presentFamily.emplace(project.archive()["render_core"]["queue_families"]["present"]);
				return;
			}
		}

		SDL_Window* window = SDL_CreateWindow("", 0, 0, 1, 1, SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN);
		if(!window)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create a window to pick physical device");

		VkSurfaceKHR surface = VK_NULL_HANDLE;
		if(SDL_Vulkan_CreateSurface(window, Render_Core::get().getInstance().get(), &surface) != SDL_TRUE)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create a surface to pick physical device");

		int i = 0;
		for(const auto& device : devices)
		{
			if(saved_index != -1 && saved_index != i)
				continue;
			if(isDeviceSuitable(device, surface))
			{
				_physicalDevice = device;
				project.archive()["render_core"]["physical_device"] = i;
				project.archive()["render_core"]["queue_families"]["graphics"] = Render_Core::get().getQueue().getFamilies().graphicsFamily.value();
				project.archive()["render_core"]["queue_families"]["present"] = Render_Core::get().getQueue().getFamilies().presentFamily.value();
				break;
			}
			i++;
		}

		vkDestroySurfaceKHR(Render_Core::get().getInstance().get(), surface, nullptr);
		SDL_DestroyWindow(window);

		if(_physicalDevice == VK_NULL_HANDLE)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to find a suitable GPU");
		Core::log::report(DEBUGLOG, "Vulkan : picked a physical device");
	}

	bool Device::isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		Queues::QueueFamilyIndices indices = Render_Core::get().getQueue().findQueueFamilies(device, surface);

		bool extensionsSupported = checkDeviceExtensionSupport(device);

		uint32_t formatCount = 0;
		if(extensionsSupported)
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
		return indices.isComplete() && extensionsSupported && formatCount != 0;
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
