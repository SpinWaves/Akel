// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_DRIVERS_VULKAN_PRE_COMPILED_HEADER__
#define __AK_DRIVERS_VULKAN_PRE_COMPILED_HEADER__

#include <Core/CompilationProfile.h>
#include <Drivers/Vulkan/Vulkan.h>

#include <vulkan/vulkan_core.h>

#ifdef VK_USE_PLATFORM_ANDROID_KHR
	#include <vulkan/vulkan_android.h>
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
	#include <vulkan/vulkan_wayland.h>
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
	typedef struct HINSTANCE__* HINSTANCE;
	typedef struct HWND__* HWND;
	typedef struct HMONITOR__* HMONITOR;
	typedef void* HANDLE;
	typedef /*_Null_terminated_*/ const wchar_t* LPCWSTR;
	typedef unsigned long DWORD;
	typedef struct _SECURITY_ATTRIBUTES SECURITY_ATTRIBUTES;
	#include <vulkan/vulkan_win32.h>
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
	struct xcb_connection_t;
	typedef uint32_t xcb_window_t;
	typedef uint32_t xcb_visualid_t;
	#include <vulkan/vulkan_xcb.h>
#endif

#ifdef VK_USE_PLATFORM_METAL_EXT
	#include <vulkan/vulkan_metal.h>
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
	typedef struct _XDisplay Display;
	typedef unsigned long XID;
	typedef XID Window;
	typedef unsigned long VisualID;
	#include <vulkan/vulkan_xlib.h>
#endif

#include <array>
#include <vector>
#include <algorithm>

#ifdef AK_VULKAN_DEBUG
	constexpr bool VULKAN_DEBUG = true;
#else
	constexpr bool VULKAN_DEBUG = false;
#endif

#endif
