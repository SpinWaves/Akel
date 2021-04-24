// This file is a part of AtlasEngine
// CREATED : 23/04/2021
// UPDATED : 24/04/2021

#include <Core/core.h>
#include <Platform/platform.h>

namespace AE::Core
{
    GPU::GPU()
    {   
        vendors[0x1002] = "AMD";
        vendors[0x1010] = "ImgTec";
        vendors[0x10DE] = "NVIDIA";
        vendors[0x13B5] = "ARM";
        vendors[0x5143] = "Qualcomm";
        vendors[0x8086] = "INTEL";

        if(isVulkanSupported())
        {
            VkInstanceCreateInfo createInfo{};
            createInfo.enabledLayerCount = 0;

            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

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
            bool isAlreadyOpenGLContext = false;
            uint16_t wins = Window::getNumberOfWindows();
            for(int i = 0; i < wins; i++)
            {
                if(Window::isWindowOpenGL(i))
                {
                    isAlreadyOpenGLContext = true;
                    break;
                }
                    
            }
            if(!isAlreadyOpenGLContext)
            {
                _tempoWin = SDL_CreateWindow("", 0, 0, 1, 1, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
                if(!_tempoWin)
                    messageBox(ERROR, "Unable to get GPU info", SDL_GetError());
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
    }

    uint32_t GPU::getNumberOfDevices()
    {
        return _deviceCount;
    }

    std::string GPU::getModelName()
    {
        if(useVulkan)
            return std::string(_deviceProperties.deviceName);
        return std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    }

    std::string GPU::getVendorName()
    {
        if(useVulkan)
            return vendors[_deviceProperties.vendorID];
        return std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    }

    uint32_t GPU::getVulkanVersion()
    {
        if(useVulkan)
            return _deviceProperties.apiVersion;
        return 0;
    }

    GPU::~GPU()
    {
        if(isVulkanSupported())
            vkDestroyInstance(_instance, nullptr);
        else
        {
            if(_context)
                SDL_GL_DeleteContext(_context);
            if(_tempoWin)
                SDL_DestroyWindow(_tempoWin);
        }
    }
}
