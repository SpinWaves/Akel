// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_VULKAN_SURFACE_H
#define AK_VULKAN_SURFACE_H

#include <Drivers/Vulkan/PreCompiled.h>
#include <Graphics/RHI/RHISurface.h>

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

namespace Ak
{
	class AK_VULKAN_API VulkanSurface : public RHISurface
	{
		public:
			VulkanSurface(class VulkanInstance& instance, const class WindowComponent& window);

			AK_FORCEINLINE VkSurfaceKHR Get() const noexcept { return m_surface; }

			~VulkanSurface() override;

		private:
			#ifdef VK_USE_PLATFORM_ANDROID_KHR
				// VK_KHR_android_surface
				void Create(ANativeWindow* window, VkAndroidSurfaceCreateFlagsKHR flags = 0, const VkAllocationCallbacks* allocator = nullptr);
			#endif

			#ifdef VK_USE_PLATFORM_XCB_KHR
				// VK_KHR_xcb_surface
				void Create(xcb_connection_t* connection, xcb_window_t window, VkXcbSurfaceCreateFlagsKHR flags = 0, const VkAllocationCallbacks* allocator = nullptr);
			#endif

			#ifdef VK_USE_PLATFORM_XLIB_KHR
				// VK_KHR_xlib_surface
				void Create(Display* display, ::Window window, VkXlibSurfaceCreateFlagsKHR flags = 0, const VkAllocationCallbacks* allocator = nullptr);
			#endif

			#ifdef VK_USE_PLATFORM_WAYLAND_KHR
				// VK_KHR_wayland_surface
				void Create(wl_display* display, wl_surface* surface, VkWaylandSurfaceCreateFlagsKHR flags = 0, const VkAllocationCallbacks* allocator = nullptr);
			#endif

			#ifdef VK_USE_PLATFORM_WIN32_KHR
				// VK_KHR_win32_surface
				void Create(HINSTANCE instance, HWND handle, VkWin32SurfaceCreateFlagsKHR flags = 0, const VkAllocationCallbacks* allocator = nullptr);
			#endif

			#ifdef VK_USE_PLATFORM_METAL_EXT
				void Create(id layer, const VkAllocationCallbacks* allocator = nullptr);
			#endif

		private:
			VulkanInstance& m_instance;
			VkSurfaceKHR m_surface = VK_NULL_HANDLE;
	};
}

#endif
