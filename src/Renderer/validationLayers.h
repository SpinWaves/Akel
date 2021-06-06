// This file is a part of AtlasEngine
// CREATED : 06/06/2021
// UPDATED : 06/06/2021

#ifndef __AE_VK_VALIDATION_LAYERS__
#define __AE_VK_VALIDATION_LAYERS__

#include <AEpch.h>

#include <Renderer/lowestInheritance.h>

namespace AE
{
    const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

    #ifdef AE_DEBUG
        constexpr bool enableValidationLayers = true;
    #else
        constexpr bool enableValidationLayers = false;
    #endif

	class ValidationLayers : virtual public LowestInheritance
	{
		public:
			ValidationLayers();

            void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
            void setupDebugMessenger(); 

            bool checkValidationLayerSupport();
            
			static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

            VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback);

            void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator);


            VkDebugUtilsMessengerEXT debugMessenger;

	};
}

#endif // __AE_VK_VALIDATION_LAYERS__

