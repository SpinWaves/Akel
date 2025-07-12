// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/Vulkan/VulkanLoader.h>
#include <Drivers/Vulkan/VulkanInstance.h>
#include <Drivers/Vulkan/VulkanDevice.h>
#include <Core/OS/OSInstance.h>

namespace Ak
{
	VulkanLoader::VulkanLoader(VulkanInstance& instance)
	{
		#if defined(MLX_PLAT_WINDOWS)
			std::array libnames{
				"vulkan-1.dll"
			};
		#elif defined(MLX_PLAT_MACOS)
			std::array libnames{
				"libvulkan.dylib",
				"libvulkan.1.dylib",
				"libMoltenVK.dylib",
				"vulkan.framework/vulkan",
				"MoltenVK.framework/MoltenVK",
				"/usr/local/lib/libvulkan.dylib",
			};
		#else
			std::array libnames{
				"libvulkan.so.1",
				"libvulkan.so"
			};
		#endif

		for(auto libname : libnames)
		{
			m_vulkan_lib = OSInstance::GetLibLoader().Load(libname);
			if(m_vulkan_lib != NullModule)
			{
				instance.vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(OSInstance::GetLibLoader().GetSymbol(m_vulkan_lib, "vkGetInstanceProcAddr"));
				if(instance.vkGetInstanceProcAddr == nullptr)
				{
					OSInstance::GetLibLoader().UnloadLib(m_vulkan_lib);
					m_vulkan_lib = NullModule;
				}
				else
					break;
			}
		}
		if(m_vulkan_lib == NullModule)
			FatalError("Vulkan loader: failed to load libvulkan");
		DebugLog("Vulkan loader: loaded vulkan lib");
		LoadGlobal(instance);
	}

	static inline PFN_vkVoidFunction vkGetInstanceProcAddrStub(VulkanInstance& instance, const char* name, bool nullinstance)
	{
		PFN_vkVoidFunction function = instance.vkGetInstanceProcAddr(nullinstance ? nullptr : instance.Get(), name);
		if(!function)
			FatalError("Vulkan Loader: could not load '%'", name);
		return function;
	}

	static inline PFN_vkVoidFunction vkGetDeviceProcAddrStub(VulkanDevice& device, const char* name)
	{
		PFN_vkVoidFunction function = device.GetInstance().vkGetDeviceProcAddr(device.Get(), name);
		if(!function)
			FatalError("Vulkan Loader: could not load '%'", name);
		return function;
	}

	void VulkanLoader::LoadGlobal(VulkanInstance& instance)
	{
		#define AK_VULKAN_GLOBAL_FUNCTION(fn) instance.fn = reinterpret_cast<PFN_##fn>(vkGetInstanceProcAddrStub(instance, #fn, true));
			#include <Drivers/Vulkan/VulkanGlobalPrototypes.h>
		#undef AK_VULKAN_GLOBAL_FUNCTION
		DebugLog("Vulkan loader: loaded global functions");
	}

	void VulkanLoader::LoadInstance(VulkanInstance& instance)
	{
		#define AK_VULKAN_INSTANCE_FUNCTION(fn) instance.fn = reinterpret_cast<PFN_##fn>(vkGetInstanceProcAddrStub(instance, #fn, false));
			#include <Drivers/Vulkan/VulkanInstancePrototypes.h>
		#undef AK_VULKAN_INSTANCE_FUNCTION
		DebugLog("Vulkan loader: loaded instance functions");
	}

	void VulkanLoader::LoadDevice(VulkanDevice& device)
	{
		#define AK_VULKAN_DEVICE_FUNCTION(fn) device.fn = reinterpret_cast<PFN_##fn>(vkGetDeviceProcAddrStub(device, #fn));
			#include <Drivers/Vulkan/VulkanDevicePrototypes.h>
		#undef AK_VULKAN_DEVIC_FUNCTION
		DebugLog("Vulkan loader: loaded device functions");
	}

	VulkanLoader::~VulkanLoader()
	{
		OSInstance::GetLibLoader().UnloadLib(m_vulkan_lib);
		DebugLog("Vulkan loader: unloaded vulkan lib");
	}
}
