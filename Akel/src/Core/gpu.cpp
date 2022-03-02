// This file is a part of Akel
// Author : @kbz_8
// CREATED : 23/04/2021
// UPDATED : 26/06/2021

#include <Core/core.h>
#include <Platform/platform.h>
#include <Utils/utils.h>

namespace Ak::Core
{
    GPU::GPU()
    {   
        vendors[0x1002] = "AMD";
        vendors[0x1010] = "ImgTec";
        vendors[0x10DE] = "NVIDIA";
        vendors[0x13B5] = "ARM";
        vendors[0x5143] = "Qualcomm";
        vendors[0x8086] = "INTEL";

        VkInstanceCreateInfo createInfo{};
        createInfo.enabledLayerCount = 0;

        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

        if(vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
            messageBox(ERROR, "Unable to get GPU info", "Vulkan instance : unable to create vulkan instance");
        else
        {
            vkEnumeratePhysicalDevices(_instance, &_deviceCount, nullptr);
            _devices.resize(_deviceCount);
            vkEnumeratePhysicalDevices(_instance, &_deviceCount, _devices.data());
            vkGetPhysicalDeviceProperties(_devices[0], &_deviceProperties);
        }
    }

    uint32_t GPU::getNumberOfDevices()
    {
        return _deviceCount;
    }

    std::string GPU::getModelName()
    {
        return std::string(_deviceProperties.deviceName);
    }

    std::string GPU::getVendorName()
    {
        return vendors[_deviceProperties.vendorID];
    }

    uint32_t GPU::getVulkanVersion()
    {
        return _deviceProperties.apiVersion;
    }

    GPU::~GPU()
    {
        if(_instance)
            vkDestroyInstance(_instance, nullptr);
    }
}
