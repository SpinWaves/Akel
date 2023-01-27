// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 27/01/2023

#include <Renderer/Core/vk_validation_layers.h>
#include <Renderer/Core/render_core.h>
#include <Core/core.h>

namespace Ak
{
	void ValidationLayers::init()
	{
		if constexpr(!enableValidationLayers)
			return;
		if(getMainAppProjectFile().getBoolValue("vk_force_disable_validation_layers"))
			return;

		VkDebugUtilsMessengerCreateInfoEXT createInfo;
		populateDebugMessengerCreateInfo(createInfo);
		if(createDebugUtilsMessengerEXT(&createInfo, nullptr) != VK_SUCCESS)
			Core::log::report(ERROR, "Vulkan : failed to set up debug messenger");
	}

	bool ValidationLayers::checkValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for(const char* layerName : validationLayers)
        {
            bool layerFound = false;

            for(const auto& layerProperties : availableLayers)
            {
                if(std::strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if(!layerFound)
                return false;
        }
        return true;
    }

	void ValidationLayers::destroy()
	{
		if constexpr(!enableValidationLayers)
			return;
		if(getMainAppProjectFile().getBoolValue("vk_force_disable_validation_layers"))
			return;
		destroyDebugUtilsMessengerEXT(nullptr);
	}

	VkResult ValidationLayers::createDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(Render_Core::get().getInstance().get(), "vkCreateDebugUtilsMessengerEXT");
        return func != nullptr ? func(Render_Core::get().getInstance().get(), pCreateInfo, pAllocator, &_debugMessenger) : VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	void ValidationLayers::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = ValidationLayers::debugCallback;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL ValidationLayers::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{
		if(messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
		{
			std::cout << '\n';
			Core::log::report(ERROR, std::string("Vulkan layer error: ") + pCallbackData->pMessage);
		}
		else if(messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		{
			std::cout << '\n';
			Core::log::report(WARNING, std::string("Vulkan layer warning: ") + pCallbackData->pMessage);
		}
		else if(getMainAppProjectFile().getBoolValue("vk_enable_message_validation_layer"))
			std::cout << green << pCallbackData->pMessage << def << std::endl;

		return VK_FALSE;
	}

	void ValidationLayers::destroyDebugUtilsMessengerEXT(const VkAllocationCallbacks* pAllocator)
	{
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(Render_Core::get().getInstance().get(), "vkDestroyDebugUtilsMessengerEXT");
		if(func != nullptr)
			func(Render_Core::get().getInstance().get(), _debugMessenger, pAllocator);
	}
}
