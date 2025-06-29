// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include "Core/Logs.h"
#include <Drivers/Vulkan/VulkanSurface.h>
#include <Drivers/Vulkan/VulkanInstance.h>
#include <Platform/WindowComponent.h>
#include <Platform/SI/WindowBackend.h>
#include <Platform/SI/Window.h>
#include <Platform/Enums.h>

namespace Ak
{
	VulkanSurface::VulkanSurface(VulkanInstance& instance, const WindowComponent& window) : RHISurface(window), m_instance(instance)
	{
		#ifndef VK_KHR_surface
			FatalError("Vulkan: surfaces support is not present");
		#else
			WindowBackend raw_window = window.GetRawWindow()->GetWindowBackend();

			switch(raw_window.backend_in_use)
			{
				#if (defined(VK_USE_PLATFORM_XLIB_KHR) && defined(VK_KHR_xlib_surface)) || (defined(VK_USE_PLATFORM_XCB_KHR) && defined(VK_KHR_xcb_surface))
					case WindowBackendType::X11:
					{
						Display* display = static_cast<Display*>(raw_window.x11.display);
						::Window window = static_cast<::Window>(raw_window.x11.window);
						Create(display, window);
						DebugLog("Vulkan: created X11 surface");
						break;
					}
				#endif

				#if defined(VK_USE_PLATFORM_WAYLAND_KHR) && defined(VK_KHR_wayland_surface)
					case WindowBackendType::Wayland:
					{
						wl_display* display = static_cast<wl_display*>(raw_window.wayland.display);
						wl_surface* surface = static_cast<wl_surface*>(raw_window.wayland.surface);
						Create(display, surface);
						DebugLog("Vulkan: created Wayland surface");
						break;
					}
				#endif

				#if defined(VK_USE_PLATFORM_WIN32_KHR) && defined(VK_KHR_win32_surface)
					case WindowBackendType::WinAPI:
					{
						break;
					}
				#endif

				#if defined(VK_USE_PLATFORM_METAL_EXT) && defined(VK_EXT_metal_surface)
					case WindowBackendType::Cocoa:
					{
						break;
					}
				#endif

				default:
				{
					FatalError("Unhandled window type");
					break;
				}
			}
		#endif
	}

	#ifdef VK_USE_PLATFORM_ANDROID_KHR
		void VulkanSurface::Create(ANativeWindow* window, VkAndroidSurfaceCreateFlagsKHR flags, const VkAllocationCallbacks* allocator)
		{
			FatalError("Vulkan: Android surfaces is not supported yet")
		}
	#endif

	#ifdef VK_USE_PLATFORM_XCB_KHR
		void VulkanSurface::Create(xcb_connection_t* connection, xcb_window_t window, VkXcbSurfaceCreateFlagsKHR flags, const VkAllocationCallbacks* allocator)
		{
			VkXcbSurfaceCreateInfoKHR create_info{};
			create_info.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
			create_info.pNext = nullptr;
			create_info.flags = flags;
			create_info.connection = connection;
			create_info.window = window;
			CheckVk(m_instance.vkCreateXcbSurfaceKHR(m_instance.Get(), &create_info, allocator, &m_surface));
		}
	#endif

	#ifdef VK_USE_PLATFORM_XLIB_KHR
		void VulkanSurface::Create(Display* display, ::Window window, VkXlibSurfaceCreateFlagsKHR flags, const VkAllocationCallbacks* allocator)
		{
			VkXlibSurfaceCreateInfoKHR create_info{};
			create_info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
			create_info.pNext = nullptr;
			create_info.flags = flags;
			create_info.dpy = display;
			create_info.window = window;
			CheckVk(m_instance.vkCreateXlibSurfaceKHR(m_instance.Get(), &create_info, allocator, &m_surface));
		}
	#endif

	#ifdef VK_USE_PLATFORM_WAYLAND_KHR
		void VulkanSurface::Create(wl_display* display, wl_surface* surface, VkWaylandSurfaceCreateFlagsKHR flags, const VkAllocationCallbacks* allocator)
		{
			VkWaylandSurfaceCreateInfoKHR create_info{};
			create_info.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
			create_info.pNext = nullptr;
			create_info.flags = flags;
			create_info.display = display;
			create_info.surface = surface;
			CheckVk(m_instance.vkCreateWaylandSurfaceKHR(m_instance.Get(), &create_info, allocator, &m_surface));
		}
	#endif

	#ifdef VK_USE_PLATFORM_WIN32_KHR
		void VulkanSurface::Create(HINSTANCE instance, HWND handle, VkWin32SurfaceCreateFlagsKHR flags, const VkAllocationCallbacks* allocator)
		{
			FatalError("Vulkan: Windows surfaces is not supported yet")
		}
	#endif

	#ifdef VK_USE_PLATFORM_METAL_EXT
		void VulkanSurface::Create(id layer, const VkAllocationCallbacks* allocator)
		{
			FatalError("Vulkan: macOS/iOS surfaces is not supported yet")
		}
	#endif

	VulkanSurface::~VulkanSurface()
	{
		#ifndef VK_KHR_surface
			FatalError("Vulkan: Surfaces support is not present");
		#else
			m_instance.vkDestroySurfaceKHR(m_instance.Get(), m_surface, nullptr);
			DebugLog("Vulkan: destroyed surface");
		#endif
	}
}
