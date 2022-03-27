// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2022
// Updated : 27/03/2022

#include "render_core.h"
#include <Platform/window.h>
#include <Core/core.h>

namespace Ak
{
	const std::vector<const char*> Instance::validationLayers = {"VK_LAYER_KHRONOS_validation"}; // "VK_LAYER_RENDERDOC_Capture"

	VKAPI_ATTR VkBool32 VKAPI_CALL callbackDebug(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData)
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
		else if(Core::ProjectFile::getBoolValue("vk_enable_message_validation_layer"))
	    	std::cout << green << pCallbackData->pMessage << def << std::endl;

		return VK_FALSE;
	}

	VkResult Instance::fvkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger)
	{
		auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT"));
		if(func)
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	void Instance::fvkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks *pAllocator)
	{
		auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT"));
		if(func)
			return func(_instance, messenger, pAllocator);
	}

	void Instance::fvkCmdPushDescriptorSetKHR(VkDevice device, VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet *pDescriptorWrites)
	{
		auto func = reinterpret_cast<PFN_vkCmdPushDescriptorSetKHR>(vkGetDeviceProcAddr(device, "vkCmdPushDescriptorSetKHR"));
		if(func)
			func(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
	}

	uint32_t Instance::findMemoryTypeIndex(const VkPhysicalDeviceMemoryProperties *deviceMemoryProperties, const VkMemoryRequirements *memoryRequirements, VkMemoryPropertyFlags requiredProperties)
	{
		for(uint32_t i = 0; i < deviceMemoryProperties->memoryTypeCount; ++i)
		{
			if(memoryRequirements->memoryTypeBits & (1 << i))
			{
				if((deviceMemoryProperties->memoryTypes[i].propertyFlags & requiredProperties) == requiredProperties)
					return i;
			}
		}

		Core::log::report(FATAL_ERROR, "couldn't find a proper memory type");
	}

	Instance::Instance(WindowComponent* window) : _window(window) 
	{
		createInstance();
		createDebugMessenger();
	}

	bool Instance::checkValidationLayerSupport() const
	{
		uint32_t instanceLayerPropertyCount;
		vkEnumerateInstanceLayerProperties(&instanceLayerPropertyCount, nullptr);
		std::vector<VkLayerProperties> instanceLayerProperties(instanceLayerPropertyCount);
		vkEnumerateInstanceLayerProperties(&instanceLayerPropertyCount, instanceLayerProperties.data());

		for(const auto &layerName : validationLayers)
		{
			bool layerFound = false;

			for(const auto &layerProperties : instanceLayerProperties)
			{
				if(strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}

			if(!layerFound)
			{
				Core::log::report(ERROR, "Vulkan validation layer not found : %s", std::quoted(layerName));
				return false;
			}
		}
		
		return true;
	}

	std::vector<const char*> Instance::getExtensions() const
	{
		if(_window == nullptr)
			Core::log::report(FATAL_ERROR, "unable to get vulkan extensions (bad window component pointer)");

		unsigned int count = 0;
        if(!SDL_Vulkan_GetInstanceExtensions(_window->getNativeWindow(), &count, nullptr))
			Core::log::report(ERROR, "Vulkan : Cannot get instance extentions from window : %s",  SDL_GetError());

        std::vector<const char*> extensions = {
            VK_EXT_DEBUG_REPORT_EXTENSION_NAME // Sample additional extension
        };
        size_t additional_extension_count = extensions.size();
        extensions.resize(additional_extension_count + count);

        if(!SDL_Vulkan_GetInstanceExtensions(_window->getNativeWindow(), &count, extensions.data() + additional_extension_count))
			Core::log::report(ERROR, "Vulkan : Cannot get instance extentions from window : %s", SDL_GetError());

        if(_enableValidationLayers)
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        return std::move(extensions);
	}

	void Instance::createInstance()
	{
		RCore::checkVk(volkInitialize());
		
		VkApplicationInfo applicationInfo = {};
		applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		applicationInfo.pEngineName = "Akel";
		applicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
		applicationInfo.apiVersion = volkGetInstanceVersion() >= VK_API_VERSION_1_1 ? VK_API_VERSION_1_1 : VK_MAKE_VERSION(1, 0, 57);

		if(_enableValidationLayers && !checkValidationLayerSupport())
			Core::log::report(FATAL_ERROR, "Validation layers requested, but not available");

		auto extensions = getExtensions();
		
		VkInstanceCreateInfo instanceCreateInfo{};
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &applicationInfo;
		instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

		VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo{};
		if(_enableValidationLayers)
		{
			debugUtilsMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			debugUtilsMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			debugUtilsMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			debugUtilsMessengerCreateInfo.pfnUserCallback = &CallbackDebug;
			instanceCreateInfo.pNext = static_cast<VkDebugUtilsMessengerCreateInfoEXT *>(&debugUtilsMessengerCreateInfo);

			instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
		}

		RCore::checkVk(vkCreateInstance(&instanceCreateInfo, nullptr, &_instance));

		#if VOLK_HEADER_VERSION >= 131
			volkLoadInstanceOnly(_instance);
		#else
			volkLoadInstance(_instance);
		#endif
	}

	void Instance::createDebugMessenger()
	{
		if(!_enableValidationLayers)
			return;

		VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo{};
		debugUtilsMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugUtilsMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugUtilsMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugUtilsMessengerCreateInfo.pfnUserCallback = &callbackDebug;
		RCore::checkVk(fvkCreateDebugUtilsMessengerEXT(_instance, &debugUtilsMessengerCreateInfo, nullptr, &_debugMessenger));
	}

	Instance::~Instance()
	{
		fvkDestroyDebugUtilsMessengerEXT(_instance, _debugMessenger, nullptr);
		vkDestroyInstance(_instance, nullptr);
		_window = nullptr;
	}
}
