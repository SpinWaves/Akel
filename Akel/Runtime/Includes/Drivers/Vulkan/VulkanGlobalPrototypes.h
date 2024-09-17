// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

// No header guards

#ifndef AK_VULKAN_GLOBAL_FUNCTION
	#error "AK_VULKAN_GLOBAL_FUNCTION not defined"
#endif

#ifdef VK_VERSION_1_0
	AK_VULKAN_GLOBAL_FUNCTION(vkCreateDevice)
	AK_VULKAN_GLOBAL_FUNCTION(vkDestroyInstance)
	AK_VULKAN_GLOBAL_FUNCTION(vkEnumerateDeviceExtensionProperties)
	AK_VULKAN_GLOBAL_FUNCTION(vkEnumeratePhysicalDevices)
	AK_VULKAN_GLOBAL_FUNCTION(vkGetDeviceProcAddr)
	AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceFeatures)
	AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceFormatProperties)
	AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceImageFormatProperties)
	AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceMemoryProperties)
	AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceProperties)
	AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties)
#endif

#ifdef VK_KHR_surface
	AK_VULKAN_GLOBAL_FUNCTION(vkDestroySurfaceKHR)
	AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)
	AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceSurfaceFormatsKHR)
	AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceSurfacePresentModesKHR)
	AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceSurfaceSupportKHR)
#endif

#ifdef AK_VULKAN_DEBUG
	#ifdef VK_EXT_debug_report
		AK_VULKAN_GLOBAL_FUNCTION(vkCreateDebugReportCallbackEXT)
		AK_VULKAN_GLOBAL_FUNCTION(vkDestroyDebugReportCallbackEXT)
		AK_VULKAN_GLOBAL_FUNCTION(vkDebugReportMessageEXT)
	#endif

	#ifdef VK_EXT_debug_utils
		AK_VULKAN_GLOBAL_FUNCTION(vkCreateDebugUtilsMessengerEXT)
		AK_VULKAN_GLOBAL_FUNCTION(vkDestroyDebugUtilsMessengerEXT)
		AK_VULKAN_GLOBAL_FUNCTION(vkSetDebugUtilsObjectNameEXT)
		AK_VULKAN_GLOBAL_FUNCTION(vkSetDebugUtilsObjectTagEXT)
		AK_VULKAN_GLOBAL_FUNCTION(vkSubmitDebugUtilsMessageEXT)
	#endif
#endif

#ifdef VK_USE_PLATFORM_ANDROID_KHR
	#ifdef VK_KHR_android_surface
		AK_VULKAN_GLOBAL_FUNCTION(vkCreateAndroidSurfaceKHR)
	#endif
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
	#ifdef VK_KHR_xcb_surface
		AK_VULKAN_GLOBAL_FUNCTION(vkCreateXcbSurfaceKHR)
		AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceXcbPresentationSupportKHR)
	#endif
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
	#ifdef VK_KHR_xlib_surface
		AK_VULKAN_GLOBAL_FUNCTION(vkCreateXlibSurfaceKHR)
		AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceXlibPresentationSupportKHR)
	#endif
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
	#ifdef VK_KHR_wayland_surface
		AK_VULKAN_GLOBAL_FUNCTION(vkCreateWaylandSurfaceKHR)
		AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceWaylandPresentationSupportKHR)
	#endif
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
	#ifdef VK_KHR_win32_surface
		AK_VULKAN_GLOBAL_FUNCTION(vkCreateWin32SurfaceKHR)
		AK_VULKAN_GLOBAL_FUNCTION(vkGetPhysicalDeviceWin32PresentationSupportKHR)
	#endif
#endif

#ifdef VK_USE_PLATFORM_METAL_EXT
	#ifdef VK_EXT_metal_surface
		AK_VULKAN_GLOBAL_FUNCTION(vkCreateMetalSurfaceEXT)
	#endif
#endif
