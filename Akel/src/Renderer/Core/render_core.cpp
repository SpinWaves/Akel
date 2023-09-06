// This file is a part of Akel
// Authors : @kbz_8
// Created : 25/03/2022
// Updated : 06/09/2023

#include <Renderer/Core/render_core.h>
#include <Renderer/RenderPass/frame_buffer_library.h>
#include <Renderer/RenderPass/render_pass_library.h>
#include <Renderer/Images/texture_library.h>
#include <Renderer/Images/cubemap_library.h>
#include <Renderer/Pipeline/shaders_library.h>
#include <Graphics/material_library.h>

namespace Ak
{
	namespace RCore
	{
		const char* verbaliseResultVk(VkResult result)
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
		}

		uint32_t formatSize(VkFormat format)
		{
			switch(format)
			{
				case VK_FORMAT_UNDEFINED: return 0;
				case VK_FORMAT_R4G4_UNORM_PACK8: return 1;
				case VK_FORMAT_R4G4B4A4_UNORM_PACK16: return 2;
				case VK_FORMAT_B4G4R4A4_UNORM_PACK16: return 2;
				case VK_FORMAT_R5G6B5_UNORM_PACK16: return 2;
				case VK_FORMAT_B5G6R5_UNORM_PACK16: return 2;
				case VK_FORMAT_R5G5B5A1_UNORM_PACK16: return 2;
				case VK_FORMAT_B5G5R5A1_UNORM_PACK16: return 2;
				case VK_FORMAT_A1R5G5B5_UNORM_PACK16: return 2;
				case VK_FORMAT_R8_UNORM: return 1;
				case VK_FORMAT_R8_SNORM: return 1;
				case VK_FORMAT_R8_USCALED: return 1;
				case VK_FORMAT_R8_SSCALED: return 1;
				case VK_FORMAT_R8_UINT: return 1;
				case VK_FORMAT_R8_SINT: return 1;
				case VK_FORMAT_R8_SRGB: return 1;
				case VK_FORMAT_R8G8_UNORM: return 2;
				case VK_FORMAT_R8G8_SNORM: return 2;
				case VK_FORMAT_R8G8_USCALED: return 2;
				case VK_FORMAT_R8G8_SSCALED: return 2;
				case VK_FORMAT_R8G8_UINT: return 2;
				case VK_FORMAT_R8G8_SINT: return 2;
				case VK_FORMAT_R8G8_SRGB: return 2;
				case VK_FORMAT_R8G8B8_UNORM: return 3;
				case VK_FORMAT_R8G8B8_SNORM: return 3;
				case VK_FORMAT_R8G8B8_USCALED: return 3;
				case VK_FORMAT_R8G8B8_SSCALED: return 3;
				case VK_FORMAT_R8G8B8_UINT: return 3;
				case VK_FORMAT_R8G8B8_SINT: return 3;
				case VK_FORMAT_R8G8B8_SRGB: return 3;
				case VK_FORMAT_B8G8R8_UNORM: return 3;
				case VK_FORMAT_B8G8R8_SNORM: return 3;
				case VK_FORMAT_B8G8R8_USCALED: return 3;
				case VK_FORMAT_B8G8R8_SSCALED: return 3;
				case VK_FORMAT_B8G8R8_UINT: return 3;
				case VK_FORMAT_B8G8R8_SINT: return 3;
				case VK_FORMAT_B8G8R8_SRGB: return 3;
				case VK_FORMAT_R8G8B8A8_UNORM: return 4;
				case VK_FORMAT_R8G8B8A8_SNORM: return 4;
				case VK_FORMAT_R8G8B8A8_USCALED: return 4;
				case VK_FORMAT_R8G8B8A8_SSCALED: return 4;
				case VK_FORMAT_R8G8B8A8_UINT: return 4;
				case VK_FORMAT_R8G8B8A8_SINT: return 4;
				case VK_FORMAT_R8G8B8A8_SRGB: return 4;
				case VK_FORMAT_B8G8R8A8_UNORM: return 4;
				case VK_FORMAT_B8G8R8A8_SNORM: return 4;
				case VK_FORMAT_B8G8R8A8_USCALED: return 4;
				case VK_FORMAT_B8G8R8A8_SSCALED: return 4;
				case VK_FORMAT_B8G8R8A8_UINT: return 4;
				case VK_FORMAT_B8G8R8A8_SINT: return 4;
				case VK_FORMAT_B8G8R8A8_SRGB: return 4;
				case VK_FORMAT_A8B8G8R8_UNORM_PACK32: return 4;
				case VK_FORMAT_A8B8G8R8_SNORM_PACK32: return 4;
				case VK_FORMAT_A8B8G8R8_USCALED_PACK32: return 4;
				case VK_FORMAT_A8B8G8R8_SSCALED_PACK32: return 4;
				case VK_FORMAT_A8B8G8R8_UINT_PACK32: return 4;
				case VK_FORMAT_A8B8G8R8_SINT_PACK32: return 4;
				case VK_FORMAT_A8B8G8R8_SRGB_PACK32: return 4;
				case VK_FORMAT_A2R10G10B10_UNORM_PACK32: return 4;
				case VK_FORMAT_A2R10G10B10_SNORM_PACK32: return 4;
				case VK_FORMAT_A2R10G10B10_USCALED_PACK32: return 4;
				case VK_FORMAT_A2R10G10B10_SSCALED_PACK32: return 4;
				case VK_FORMAT_A2R10G10B10_UINT_PACK32: return 4;
				case VK_FORMAT_A2R10G10B10_SINT_PACK32: return 4;
				case VK_FORMAT_A2B10G10R10_UNORM_PACK32: return 4;
				case VK_FORMAT_A2B10G10R10_SNORM_PACK32: return 4;
				case VK_FORMAT_A2B10G10R10_USCALED_PACK32: return 4;
				case VK_FORMAT_A2B10G10R10_SSCALED_PACK32: return 4;
				case VK_FORMAT_A2B10G10R10_UINT_PACK32: return 4;
				case VK_FORMAT_A2B10G10R10_SINT_PACK32: return 4;
				case VK_FORMAT_R16_UNORM: return 2;
				case VK_FORMAT_R16_SNORM: return 2;
				case VK_FORMAT_R16_USCALED: return 2;
				case VK_FORMAT_R16_SSCALED: return 2;
				case VK_FORMAT_R16_UINT: return 2;
				case VK_FORMAT_R16_SINT: return 2;
				case VK_FORMAT_R16_SFLOAT: return 2;
				case VK_FORMAT_R16G16_UNORM: return 4;
				case VK_FORMAT_R16G16_SNORM: return 4;
				case VK_FORMAT_R16G16_USCALED: return 4;
				case VK_FORMAT_R16G16_SSCALED: return 4;
				case VK_FORMAT_R16G16_UINT: return 4;
				case VK_FORMAT_R16G16_SINT: return 4;
				case VK_FORMAT_R16G16_SFLOAT: return 4;
				case VK_FORMAT_R16G16B16_UNORM: return 6;
				case VK_FORMAT_R16G16B16_SNORM: return 6;
				case VK_FORMAT_R16G16B16_USCALED: return 6;
				case VK_FORMAT_R16G16B16_SSCALED: return 6;
				case VK_FORMAT_R16G16B16_UINT: return 6;
				case VK_FORMAT_R16G16B16_SINT: return 6;
				case VK_FORMAT_R16G16B16_SFLOAT: return 6;
				case VK_FORMAT_R16G16B16A16_UNORM: return 8;
				case VK_FORMAT_R16G16B16A16_SNORM: return 8;
				case VK_FORMAT_R16G16B16A16_USCALED: return 8;
				case VK_FORMAT_R16G16B16A16_SSCALED: return 8;
				case VK_FORMAT_R16G16B16A16_UINT: return 8;
				case VK_FORMAT_R16G16B16A16_SINT: return 8;
				case VK_FORMAT_R16G16B16A16_SFLOAT: return 8;
				case VK_FORMAT_R32_UINT: return 4;
				case VK_FORMAT_R32_SINT: return 4;
				case VK_FORMAT_R32_SFLOAT: return 4;
				case VK_FORMAT_R32G32_UINT: return 8;
				case VK_FORMAT_R32G32_SINT: return 8;
				case VK_FORMAT_R32G32_SFLOAT: return 8;
				case VK_FORMAT_R32G32B32_UINT: return 12;
				case VK_FORMAT_R32G32B32_SINT: return 12;
				case VK_FORMAT_R32G32B32_SFLOAT: return 12;
				case VK_FORMAT_R32G32B32A32_UINT: return 16;
				case VK_FORMAT_R32G32B32A32_SINT: return 16;
				case VK_FORMAT_R32G32B32A32_SFLOAT: return 16;
				case VK_FORMAT_R64_UINT: return 8;
				case VK_FORMAT_R64_SINT: return 8;
				case VK_FORMAT_R64_SFLOAT: return 8;
				case VK_FORMAT_R64G64_UINT: return 16;
				case VK_FORMAT_R64G64_SINT: return 16;
				case VK_FORMAT_R64G64_SFLOAT: return 16;
				case VK_FORMAT_R64G64B64_UINT: return 24;
				case VK_FORMAT_R64G64B64_SINT: return 24;
				case VK_FORMAT_R64G64B64_SFLOAT: return 24;
				case VK_FORMAT_R64G64B64A64_UINT: return 32;
				case VK_FORMAT_R64G64B64A64_SINT: return 32;
				case VK_FORMAT_R64G64B64A64_SFLOAT: return 32;
				case VK_FORMAT_B10G11R11_UFLOAT_PACK32: return 4;
				case VK_FORMAT_E5B9G9R9_UFLOAT_PACK32: return 4;

				default: return 0;
			}
		}

		void checkVk(VkResult result)
		{
			if(result != VK_SUCCESS)
				Core::log::report(result < 0 ? FATAL_ERROR : ERROR, "Vulkan error : %s", verbaliseResultVk(result));
		}

		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
		{
			VkPhysicalDeviceMemoryProperties memProperties;
			vkGetPhysicalDeviceMemoryProperties(Render_Core::get().getDevice().getPhysicalDevice(), &memProperties);

			for(uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
			{
				if((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
					return i;
			}

			Core::log::report(FATAL_ERROR, "Vulkan : failed to find suitable memory type");
		}
	}

	void Render_Core::init()
	{
		if(_is_init)
			return;
		if(!getMainAppProjectFile().keyExists("render_core"))
			getMainAppProjectFile().archive()["render_core"] = nlohmann::json::object();
		_instance.init();
		volkLoadInstance(_instance.get());
		_layers.init();
		_device.init();
		volkLoadDevice(_device.get());
		_queues.init();
		_is_init = true;
	}

	void Render_Core::destroy()
	{
		if(!_is_init)
			return;

		std::mutex mutex;
        std::unique_lock<std::mutex> watchdog(mutex, std::try_to_lock);

        vkDeviceWaitIdle(_device());

		MaterialLibrary::get().clearLibrary();
		TextureLibrary::get().clearLibrary();
		CubemapLibrary::get().clearLibrary();
		RenderPassesLibrary::get().clearCache();
		FrameBufferLibrary::get().clearCache();
		ShadersLibrary::get().clearLibrary();
		_device.destroy();
		_layers.destroy();
		_instance.destroy();

		_is_init = false;
	}
}
