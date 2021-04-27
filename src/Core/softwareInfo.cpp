// This file is a part of AtlasEngine
// CREATED : 05/04/2021
// UPDATED : 27/04/2021

#include <Core/core.h>

namespace AE::Core
{
    bool isVulkanSupported()
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        if(extensionCount != 0)
            return true;
        return false;
    }
}
