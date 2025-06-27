// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/Vulkan/PreCompiled.h>
#include <Drivers/Vulkan/VulkanInstance.h>
#include <Drivers/Vulkan/VulkanAdapter.h>
#include <Core/Logs.h>
#include <Config.h>

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

	bool IsVulkanSupported() noexcept
	{
		// TODO
		return true;
	}

	VulkanInstance::VulkanInstance() : m_loader(*this)
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

		CheckVk(vkCreateInstance(&create_info, nullptr, &m_instance));
		DebugLog("Vulkan: created new instance");

		#define AK_VULKAN_INSTANCE_FUNCTION(fn) fn = reinterpret_cast<PFN_##fn>(vkGetInstanceProcAddr(m_instance, #fn));
			#include <Drivers/Vulkan/VulkanInstancePrototypes.h>
		#undef AK_VULKAN_INSTANCE_FUNCTION
		DebugLog("Vulkan loader: loaded instance functions");
	}

	SharedPtr<RHIAdapter> VulkanInstance::PickAdapter(AdapterMinimalSpecs specs)
	{
		std::uint32_t count;
		vkEnumeratePhysicalDevices(m_instance, &count, nullptr);
		std::vector<VkPhysicalDevice> devices(count);
		vkEnumeratePhysicalDevices(m_instance, &count, devices.data());

		std::array type_order{
			VK_PHYSICAL_DEVICE_TYPE_OTHER,
			VK_PHYSICAL_DEVICE_TYPE_CPU,
			VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU,
			VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,
			VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
		};

		if(count > 1)
		{
			std::sort(devices.begin(), devices.end(), [this, &type_order](VkPhysicalDevice lhs, VkPhysicalDevice rhs)
			{
				VkPhysicalDeviceProperties lhs_properties;
				vkGetPhysicalDeviceProperties(lhs, &lhs_properties);
				VkPhysicalDeviceProperties rhs_properties;
				vkGetPhysicalDeviceProperties(rhs, &rhs_properties);

				VkPhysicalDeviceMemoryProperties lhs_memory_properties;
				vkGetPhysicalDeviceMemoryProperties(lhs, &lhs_memory_properties);
				VkPhysicalDeviceMemoryProperties rhs_memory_properties;
				vkGetPhysicalDeviceMemoryProperties(rhs, &rhs_memory_properties);

				if(type_order[lhs_properties.deviceType] == type_order[rhs_properties.deviceType])
					return lhs_memory_properties.memoryHeaps[0].size > rhs_memory_properties.memoryHeaps[0].size;
				return type_order[lhs_properties.deviceType] > type_order[rhs_properties.deviceType];
			});
		}

		for(auto device : devices)
		{
			VkPhysicalDeviceProperties properties;
			vkGetPhysicalDeviceProperties(device, &properties);
			VkPhysicalDeviceMemoryProperties memory_properties;
			vkGetPhysicalDeviceMemoryProperties(device, &memory_properties);

			std::uint64_t memory = static_cast<uint64_t>(memory_properties.memoryHeaps[0].size);
			std::uint32_t memory_mb = static_cast<uint32_t>(memory / 1024 / 1024);

			if(specs.type != AdapterType::Any)
			{
				switch(specs.type)
				{
					case AdapterType::Other:
					{
						if(properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_OTHER)
							continue;
					}
					case AdapterType::CPU:
					{
						if(properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_CPU)
							continue;
					}
					case AdapterType::Virtual:
					{
						if(properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU)
							continue;
					}
					case AdapterType::Integrated:
					{
						if(properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
							continue;
					}
					case AdapterType::Discrete:
					{
						if(properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
							continue;
					}

					default : break;
				}
			}

			if(specs.vendors != AdapterVendorAny)
			{
				auto ids = ConvertAdapterVendorsToVulkanPhysicalDeviceVendorIDs(specs.vendors);
				auto it = std::find_if(ids.begin(), ids.end(), [properties](VulkanPhysicalDeviceVendorID id)
				{
					return static_cast<std::uint32_t>(id) == properties.vendorID;
				});
				if(it == ids.end())
					continue;
			}

			if(memory_mb < specs.memory)
				continue;

			SharedPtr<RHIAdapter> adapter = MakeShared<VulkanAdapter>(*this, device);
			return adapter;
		}

		return nullptr;
	}

	VulkanInstance::~VulkanInstance()
	{
		vkDestroyInstance(m_instance, nullptr);
		m_instance = VK_NULL_HANDLE;
		DebugLog("Vulkan: destroyed an instance");
	}
}

extern "C"
{
	AK_EXPORT_API Ak::VulkanInstance* AkelLoadInstance()
	{
		return Ak::MemAlloc<Ak::VulkanInstance>();
	}
}
