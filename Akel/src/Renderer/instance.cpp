// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2021
// Updated : 28/02/2022

#include <Renderer/rendererComponent.h>
#include <Platform/platform.h>
#include <Utils/utils.h>
#include <Core/core.h>

namespace Ak
{
    std::vector<const char*> RendererComponent::getRequiredExtensions()
    {
        unsigned int count;
        if(!SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr))
			Core::log::report(ERROR, "Vulkan : Cannot get instance extentions from window : %s",  SDL_GetError());

        std::vector<const char*> extensions = {
            VK_EXT_DEBUG_REPORT_EXTENSION_NAME // Sample additional extension
        };
        size_t additional_extension_count = extensions.size();
        extensions.resize(additional_extension_count + count);

        if(!SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data() + additional_extension_count))
			Core::log::report(ERROR, "Vulkan : Cannot get instance extentions from window : %s", SDL_GetError());

        if(enableValidationLayers)
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        return std::move(extensions);
    }

    void RendererComponent::createInstance()
    {
        if(enableValidationLayers && !checkValidationLayerSupport())
			Core::log::report(ERROR, "Vulkan : Layer validations are enabled but not available");

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = SDL_GetWindowTitle(window);
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Akel";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if(enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        }
        else
        {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : Failed to create Vulkan instance");
    }
}
