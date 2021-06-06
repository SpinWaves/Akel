// This file is a part of AtlasEngine
// CREATED : 05/06/2021
// UPDATED : 05/06/2021

#ifndef __AE_VK_DEVICE__
#define __AE_VK_DEVICE__

#include <AEpch.h>

#include <Renderer/imageView.h>

namespace AE
{
	const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
	
	class Device : public ImageView
	{
		public:
			Device();

            void pickPhysicalDevice();
            bool isDeviceSuitable(VkPhysicalDevice device);
            void createLogicalDevice();
			bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	};
}

#endif // __AE_VK_DEVICE__

