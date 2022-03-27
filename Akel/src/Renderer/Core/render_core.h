// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/03/2022
// Updated : 25/03/2022

#ifndef __AK_RENDER_CORE__
#define __AK_RENDER_CORE__

#include <Akpch.h>
#include <Renderer/Core/Memory/memory_GPU.h>

#include "physicalDevice.h"
#include "logicalDevice.h"
#include "instance.h"
#include "surface.h"

namespace Ak::RCore
{
    void checkVk(VkResult result);

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
}

#endif // __AK_RENDER_CORE__
