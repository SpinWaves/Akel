// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

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
