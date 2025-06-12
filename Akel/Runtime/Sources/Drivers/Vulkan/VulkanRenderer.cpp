// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include "Utils/Result.h"
#include <Drivers/Vulkan/VulkanRenderer.h>
#include <Core/Memory/MemoryManager.h>
#include <Core/Logs.h>

#if defined(AK_PLAT_WINDOWS)
	constexpr const char* VULKAN_LIB_NAME = "vulkan-1.dll";
#elif defined(AK_PLAT_MACOS)
	constexpr const char* VULKAN_LIB_NAME = "libvulkan.dylib / libvulkan.1.dylib / libMoltenVK.dylib";
#else
	constexpr const char* VULKAN_LIB_NAME = "libvulkan.so / libvulkan.so.1";
#endif

namespace Ak
{
	namespace Internal
	{
		void ErrorCallback(const char* message) noexcept
		{
			FatalError(message);
		}

		void ValidationErrorCallback(const char* message) noexcept
		{
			Error(message);
		}

		void ValidationWarningCallback(const char* message) noexcept
		{
			Warning(message);
		}
	}

	const char* VerbaliseVkResult(VkResult result) noexcept
	{
		switch(result)
		{
			case VK_SUCCESS: return "Success";
			case VK_NOT_READY: return "A fence or query has not yet completed";
			case VK_TIMEOUT: return "A wait operation has not completed in the specified time";
			case VK_EVENT_SET: return "An event is signaled";
			case VK_EVENT_RESET: return "An event is unsignaled";
			case VK_INCOMPLETE: return "A return array was too small for the result";
			case VK_ERROR_OUT_OF_HOST_MEMORY: return "A host memory allocation has failed";
			case VK_ERROR_OUT_OF_DEVICE_MEMORY: return "A device memory allocation has failed";
			case VK_ERROR_INITIALIZATION_FAILED: return "Initialization of an object could not be completed for implementation-specific reasons";
			case VK_ERROR_DEVICE_LOST: return "The logical or physical device has been lost";
			case VK_ERROR_MEMORY_MAP_FAILED: return "Mapping of a memory object has failed";
			case VK_ERROR_LAYER_NOT_PRESENT: return "A requested layer is not present or could not be loaded";
			case VK_ERROR_EXTENSION_NOT_PRESENT: return "A requested extension is not supported";
			case VK_ERROR_FEATURE_NOT_PRESENT: return "A requested feature is not supported";
			case VK_ERROR_INCOMPATIBLE_DRIVER: return "The requested version of Vulkan is not supported by the driver or is otherwise incompatible";
			case VK_ERROR_TOO_MANY_OBJECTS: return "Too many objects of the type have already been created";
			case VK_ERROR_FORMAT_NOT_SUPPORTED: return "A requested format is not supported on this device";
			case VK_ERROR_SURFACE_LOST_KHR: return "A surface is no longer available";
			case VK_SUBOPTIMAL_KHR: return "A swapchain no longer matches the surface properties exactly, but can still be used";
			case VK_ERROR_OUT_OF_DATE_KHR: return "A surface has changed in such a way that it is no longer compatible with the swapchain";
			case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: return "The display used by a swapchain does not use the same presentable image layout";
			case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: return "The requested window is already connected to a VkSurfaceKHR, or to some other non-Vulkan API";
			case VK_ERROR_VALIDATION_FAILED_EXT: return "A validation layer found an error";

			default: return "Unknown Vulkan error";
		}
		return nullptr; // just to avoid warnings
	}

	void CheckVk(VkResult result) noexcept
	{
		if(result < VK_SUCCESS)
			FatalError("Vulkan check failed: %", VerbaliseVkResult(result));
		else if(result > VK_SUCCESS)
			Warning("Vulkan check failed: %", VerbaliseVkResult(result));
	}

	VulkanRenderer* VulkanRenderer::s_instance = nullptr;

	VulkanRenderer::VulkanRenderer() : m_loader(*this)
	{
		s_instance = this;
		p_instance = MakeUnique<VulkanInstance>();
	}

	std::uint32_t VulkanRenderer::LoadNewDevice(const PhysicalDeviceMinimalSpecs& specs) noexcept
	{
		m_devices.emplace_back(specs);
		return static_cast<std::uint32_t>(m_devices.size() - 1);
	}

	VulkanRenderer::~VulkanRenderer()
	{
		m_devices.clear();
		p_instance.Reset();
		s_instance = nullptr;
	}
}

extern "C"
{
	AK_EXPORT_API Ak::RHIRenderer* AkelLoadRendererDriver()
	{
		return Ak::MemAlloc<Ak::VulkanRenderer>();
	}
}
