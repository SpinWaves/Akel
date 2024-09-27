// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/Vulkan/VulkanLoader.h>
#include <Drivers/Vulkan/VulkanInstance.h>
#include <Drivers/Vulkan/VulkanRenderer.h>
#include <Core/OS/OSInstance.h>

namespace Ak
{
	VulkanLoader::VulkanLoader()
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
				vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(OSInstance::GetLibLoader().GetSymbol(m_vulkan_lib, "vkGetInstanceProcAddr"));
				if(vkGetInstanceProcAddr == nullptr)
				{
					OSInstance::GetLibLoader().UnloadLib(m_vulkan_lib);
					m_vulkan_lib = NullModule;
				}
				else
					break;
			}
		}
		if(m_vulkan_lib == NullModule)
			FatalError("Vulkan loader : failed to load libvulkan");
		DebugLog("Vulkan loader : loaded vulkan lib");
		LoadGlobal();
	}

	void VulkanLoader::LoadGlobal()
	{
		#define AK_VULKAN_GLOBAL_FUNCTION(fn) fn = reinterpret_cast<PFN_##fn>(vkGetInstanceProcAddr(nullptr, #fn));
			#include <Drivers/Vulkan/VulkanGlobalPrototypes.h>
		#undef AK_VULKAN_GLOBAL_FUNCTION
		DebugLog("Vulkan loader : loaded global functions");
	}

	VulkanLoader::~VulkanLoader()
	{
		OSInstance::GetLibLoader().UnloadLib(m_vulkan_lib);
		DebugLog("Vulkan loader : unloaded vulkan lib");
	}

	#define AK_VULKAN_GLOBAL_FUNCTION(fn) PFN_##fn fn = nullptr;
		#include <Drivers/Vulkan/VulkanGlobalPrototypes.h>
	#undef AK_VULKAN_GLOBAL_FUNCTION
}