// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

// No header guards

#ifndef AK_VULKAN_GLOBAL_FUNCTION
	#error "AK_VULKAN_GLOBAL_FUNCTION not defined"
#endif

#ifdef VK_VERSION_1_0
	AK_VULKAN_GLOBAL_FUNCTION(vkCreateInstance)
	AK_VULKAN_GLOBAL_FUNCTION(vkEnumerateInstanceExtensionProperties)
	AK_VULKAN_GLOBAL_FUNCTION(vkEnumerateInstanceLayerProperties)
	AK_VULKAN_GLOBAL_FUNCTION(vkGetInstanceProcAddr)
#endif
