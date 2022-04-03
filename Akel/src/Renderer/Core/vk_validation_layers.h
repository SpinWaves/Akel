// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 03/04/2022

#ifndef __AK_VK_VALIDATON_LAYERS__
#define __AK_VK_VALIDATON_LAYERS__

#include <Akpch.h>

namespace Ak
{
	class ValidationLayers
	{
		public:
			void init();
			void destroy();
			bool checkValidationLayerSupport();

		private:
			VkResult createDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator);
			void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
			VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
			void destroyDebugUtilsMessengerEXT(const VkAllocationCallbacks* pAllocator);

			VkDebugUtilsMessengerEXT _debugMessenger;
	};
}

#endif // __AK_VK_VALIDATION_LAYERS__
