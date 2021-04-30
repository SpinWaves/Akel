// This file is a part of AtlasEngine
// CREATED : 05/04/2021
// UPDATED : 30/04/2021

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

    void printEngineInfo()
    {
        std::cout << "          _   _           ______             _             " << std::endl;
        std::cout << "     /\\  | | | |         |  ____|           (_)            " << std::endl;
        std::cout << "    /  \\ | |_| | __ _ ___| |__   _ __   __ _ _ _ __   ___  " << std::endl;
        std::cout << "   / /\\ \\| __| |/ _` / __|  __| | '_ \\ / _` | | '_ \\ / _ \\ " << std::endl;
        std::cout << "  / ____ \\ |_| | (_| \\__ \\ |____| | | | (_| | | | | |  __/ " << std::endl;
        std::cout << " /_/    \\_\\__|_|\\__,_|___/______|_| |_|\\__, |_|_| |_|\\___| " << std::endl;
        std::cout << "                                        __/ |              " << std::endl;
        std::cout << "                                       |___/               " << std::endl;
    }
}
