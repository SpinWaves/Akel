// This file is a part of AtlasEngine
// CREATED : 23/04/2021
// UPDATED : 23/04/2021

#include <Core/core.h>
#include <Platform/platform.h>

namespace AE::Core
{
    GPU::GPU()
    {   uint32_t flags;
        if(isVulkanSupported())
            flags = SDL_WINDOW_HIDDEN | SDL_WINDOW_VULKAN;
        else
            flags = SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL;
        _tempoWin = SDL_CreateWindow("", 0, 0, 1, 1, flags);
        if(!_tempoWin)
            messageBox(ERROR, "Unable to get GPU info", SDL_GetError());
        else
        {
            if(isVulkanSupported())
            {
                VkInstanceCreateInfo createInfo{};
                createInfo.enabledLayerCount = 0;

                createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

                uint32_t extensionCount;
                SDL_Vulkan_GetInstanceExtensions(_tempoWin, &extensionCount, nullptr);
                std::vector<const char*> extensionNames(extensionCount);
                SDL_Vulkan_GetInstanceExtensions(_tempoWin, &extensionCount, extensionNames.data());

                createInfo.enabledExtensionCount = extensionNames.size();
                createInfo.ppEnabledExtensionNames = extensionNames.data();

                createInfo.enabledLayerCount = 0;

                if(vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
                    messageBox(FATAL_ERROR, "Unable to get GPU info", SDL_GetError());
                else
                {
                    useVulkan = true;
                    vkEnumeratePhysicalDevices(_instance, &_deviceCount, nullptr);
                    _devices.resize(_deviceCount);
                    vkEnumeratePhysicalDevices(_instance, &_deviceCount, _devices.data());
                    vkGetPhysicalDeviceProperties(_devices[0], &_deviceProperties);
                }
            }
            else
            {
                useVulkan = false;
                _context = SDL_GL_CreateContext(_tempoWin);
                if(!_context)
                    messageBox(ERROR, "Unable to get GPU info", SDL_GetError());
                GLuint GLEWerr = glewInit();
                if(GLEW_OK != GLEWerr)
                    messageBox(ERROR, "Unable to get GPU info", std::string(reinterpret_cast<AE_text>(glewGetErrorString(GLEWerr))));
            }
        }
    }

    uint8_t GPU::getNumberOfDevices()
    {
        return _deviceCount;
    }

    std::string GPU::getModelName()
    {
        if(useVulkan)
            return std::string(_deviceProperties.deviceName);
    }

    GPU::~GPU()
    {
        SDL_DestroyWindow(_tempoWin);
        vkDestroyInstance(_instance, nullptr);
    }
}
