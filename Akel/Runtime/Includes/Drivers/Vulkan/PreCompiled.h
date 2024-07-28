// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 28/07/2024

#ifndef __AK_DRIVERS_VULKAN_PRE_COMPILED_HEADER__
#define __AK_DRIVERS_VULKAN_PRE_COMPILED_HEADER__

#include <Core/CompilationProfile.h>
#include <Drivers/Vulkan/Vulkan.h>

#include <volk.h>

#define KVF_IMPL_VK_NO_PROTOTYPES
#include <kvf.h>

#include <vector>

#ifdef AK_VULKAN_DEBUG
	constexpr bool VULKAN_DEBUG = true;
#else
	constexpr bool VULKAN_DEBUG = false;
#endif

#endif
