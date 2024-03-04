// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/02/2024
// Updated : 04/03/2024

#include <Drivers/Vulkan/PreCompiled.h>
#include <Drivers/Vulkan/VulkanAPIHandle.h>
#include <Drivers/Vulkan/VulkanRenderer.h>
#include <Core/Logs.h>

namespace Ak
{
	VulkanAPIHandle::VulkanAPIHandle() : RHIAPIHandle()
	{
		VkApplicationInfo app_info{};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pEngineName = "Akel";
		app_info.engineVersion = VK_MAKE_VERSION(0, 0, 1);
		app_info.apiVersion = VK_API_VERSION_1_3;

		std::vector<const char*> extensions;
		extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
		#ifdef VK_USE_PLATFORM_XCB_KHR
			extensions.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
		#endif

		#ifdef VK_USE_PLATFORM_XLIB_KHR
			extensions.push_back(VK_KHR_XLIB_SURFACE_EXTENSION_NAME);
		#endif

		#ifdef VK_USE_PLATFORM_WAYLAND_KHR
			extensions.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
		#endif

		#ifdef VK_USE_PLATFORM_WIN32_KHR
			extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
		#endif

		#ifdef VK_USE_PLATFORM_METAL_EXT
			extensions.push_back(VK_EXT_METAL_SURFACE_EXTENSION_NAME);
		#endif

		if constexpr(VULKAN_DEBUG)
		{
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		VkInstanceCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.pApplicationInfo = &app_info;
		create_info.enabledExtensionCount = static_cast<std::uint32_t>(extensions.size());
		create_info.ppEnabledExtensionNames = extensions.data();
		create_info.enabledLayerCount = 0; // will be replaced if validation layers are enabled
		create_info.pNext = nullptr;

		VkDebugUtilsMessengerCreateInfoEXT debug_create_info;
		if constexpr(VULKAN_DEBUG)
		{
			/*
			if(Render_Core::get().getLayers().checkValidationLayerSupport())
			{
				create_nfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
				create_nfo.ppEnabledLayerNames = validationLayers.data();
				Render_Core::get().getLayers().populateDebugMessengerCreateInfo(debugCreateInfo);
				create_nfo.pNext = static_cast<VkDebugUtilsMessengerCreateInfoEXT*>(&debugCreateInfo);
			}
			*/
		}

		VkResult res;
		if((res = vkCreateInstance(&create_info, nullptr, &m_instance)) != VK_SUCCESS)
			FatalError("Vulkan : failed to create Vulkan instance, %", VerbaliseVkResult(res));
		volkLoadInstance(m_instance);
		DebugLog("Vulkan : created new instance");
	}

	VulkanAPIHandle::~VulkanAPIHandle()
	{
		vkDestroyInstance(m_instance, nullptr);
		m_instance = VK_NULL_HANDLE;
		DebugLog("Vulkan : destroyed an instance");
	}
}
