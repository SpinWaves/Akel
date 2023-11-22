// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/04/2021
// Updated : 21/11/2023

#include <Core/core.h>
#include <Utils/utils.h>
#include <Renderer/Core/render_core.h>

namespace Ak::Core
{
    GPU::GPU()
    {   
        _vendors[0x1002] = "AMD";
        _vendors[0x1010] = "ImgTec";
        _vendors[0x10DE] = "Nvidia";
        _vendors[0x13B5] = "ARM";
        _vendors[0x5143] = "Qualcomm";
        _vendors[0x8086] = "Intel";

        _types[0] = "Other";
        _types[1] = "Integrated";
        _types[2] = "Graphics Card";
        _types[3] = "Virtual";
        _types[4] = "CPU";

		Render_Core::get().init();
		vkGetPhysicalDeviceProperties(Render_Core::get().getDevice().getPhysicalDevice(), &_deviceProperties);

        auto FN_vkEnumerateInstanceVersion = PFN_vkEnumerateInstanceVersion(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"));
        if(vkEnumerateInstanceVersion)
            vkEnumerateInstanceVersion(&_instanceVersion);
    }
}
