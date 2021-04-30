// This file is a part of AtlasEngine
// CREATED : 05/04/2021
// UPDATED : 28/04/2021

#include <Core/core.h>

namespace AE::Core
{
    bool isVulkanSupported()
    {
        VkInstance instance;
	    VkInstanceCreateInfo createInfo{};
	    createInfo.enabledLayerCount = 0;
	    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO; 
        if(vkCreateInstance(&createInfo, nullptr, &instance) == VK_SUCCESS)
            return true;
        return false;
    }
}
