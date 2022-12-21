// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 21/12/2022

#include <Core/core.h>
#include "vk_instance.h"
#include <Platform/window.h>
#include <Utils/assert.h>
#include "render_core.h"

namespace Ak
{
	namespace RCore { const char* verbaliseResultVk(VkResult result); }

	void Instance::init()
	{
		if(enableValidationLayers && !getMainAppProjectFile().getBoolValue("vk_force_disable_validation_layers") && !Render_Core::get().getLayers().checkValidationLayerSupport())
			Core::log::report(ERROR, "Vulkan : validations layers are enabled but not available");

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Akel application";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Akel";
        appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;

		if(enableValidationLayers && !getMainAppProjectFile().getBoolValue("vk_force_disable_validation_layers") && Render_Core::get().getLayers().checkValidationLayerSupport())
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
            Render_Core::get().getLayers().populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        }
        else
        {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

		VkResult res;
        if((res = vkCreateInstance(&createInfo, nullptr, &_instance)) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create Vulkan instance : %s", RCore::verbaliseResultVk(res));
	}

	std::vector<const char*> Instance::getRequiredExtensions()
    {
		SDL_Window* window = SDL_CreateWindow("", 0, 0, 1, 1, SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN);
		if(!window)
			Core::log::report(FATAL_ERROR, "Vulkan : cannot get instance extentions from window : %s",  SDL_GetError());
        unsigned int count = 0;
        if(!SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr))
			Core::log::report(ERROR, "Vulkan : cannot get instance extentions from window : %s",  SDL_GetError());

        std::vector<const char*> extensions = { VK_EXT_DEBUG_REPORT_EXTENSION_NAME };
        size_t additional_extension_count = extensions.size();
        extensions.resize(additional_extension_count + count);

        if(!SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data() + additional_extension_count))
			Core::log::report(ERROR, "Vulkan : cannot get instance extentions from window : %s", SDL_GetError());

        if(enableValidationLayers && !getMainAppProjectFile().getBoolValue("vk_force_disable_validation_layers"))
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		SDL_DestroyWindow(window);
        return extensions;
    }

    void Instance::destroy() noexcept
    {
        Ak_assert(_instance != VK_NULL_HANDLE, "trying to destroy an uninit instance");
        vkDestroyInstance(_instance, nullptr);
    }
}
