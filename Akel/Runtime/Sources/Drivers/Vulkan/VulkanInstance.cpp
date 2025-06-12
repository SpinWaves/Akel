// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/Vulkan/PreCompiled.h>
#include <Drivers/Vulkan/VulkanInstance.h>
#include <Drivers/Vulkan/VulkanRenderer.h>
#include <Core/Logs.h>
#include <Config.h>

namespace Ak
{
	VulkanInstance::VulkanInstance()
	{
		VkApplicationInfo app_info{};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pEngineName = "Akel";
		app_info.engineVersion = VK_MAKE_VERSION(AKEL_VERSION_MAJOR, AKEL_VERSION_MINOR, AKEL_VERSION_PATCH);
		app_info.apiVersion = VK_API_VERSION_1_0;

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
		}

		CheckVk(VulkanRenderer::Get().vkCreateInstance(&create_info, nullptr, &m_instance));
		DebugLog("Vulkan: created new instance");

		#define AK_VULKAN_INSTANCE_FUNCTION(fn) fn = reinterpret_cast<PFN_##fn>(VulkanRenderer::Get().vkGetInstanceProcAddr(m_instance, #fn));
			#include <Drivers/Vulkan/VulkanInstancePrototypes.h>
		#undef AK_VULKAN_INSTANCE_FUNCTION
		DebugLog("Vulkan loader: loaded instance functions");
	}

	VulkanInstance::~VulkanInstance()
	{
		vkDestroyInstance(m_instance, nullptr);
		m_instance = VK_NULL_HANDLE;
		DebugLog("Vulkan: destroyed an instance");
	}
}
