// This file is a part of AtlasEngine
// CREATED : 10/04/2021
// UPDATED : 27/04/2021

#include <Renderer/renderer.h>
#include <Platform/platform.h>
#include <Utils/utils.h>
#include <Core/core.h>

namespace AE
{
    void Instance::init(SDL_Window* window)
    {
        if(enableValidationLayers && !checkValidationLayerSupport())
            messageBox(ERROR, "Vulkan layers are not availble", "Vulkan error");

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = SDL_GetWindowTitle(window);
        appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
        appInfo.pEngineName = "AtlasEngine";
        appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        VkInstanceCreateInfo createInfo{};
        if(enableValidationLayers) 
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else
            createInfo.enabledLayerCount = 0;

        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t extensionCount;
        SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);
        std::vector<const char*> extensionNames(extensionCount);
        SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensionNames.data());

        createInfo.enabledExtensionCount = extensionNames.size();
        createInfo.ppEnabledExtensionNames = extensionNames.data();

        createInfo.enabledLayerCount = 0;

        if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
            messageBox(FATAL_ERROR, "Can't init Vulkan instance", AE_CATCH_VK_INSTANCE_CREATION);
        else
            std::cout << bg_green << "Instance created successfully" << bg_def << std::endl;
    }

    bool Instance::checkValidationLayerSupport()
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
                if(strcmp(layerName, layerProperties.layerName) == 0)
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

    void Instance::destroy()
    {
        if(instance)
            vkDestroyInstance(instance, nullptr);
    }

    Instance::~Instance()
    {
        destroy();
    }
}
