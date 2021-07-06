// This file is a part of Akel
// CREATED : 05/04/2021
// UPDATED : 06/07/2021

#include <Core/core.h>
#include <Utils/utils.h>

namespace Ak::Core
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
        std::cout << bold
		<< "    ___     __          __ 		" << '\n'
		<< "   /   |   / /__ ___   / /		" << '\n'
		<< "  / /| |  / //_// _ \\ / / 		" << '\n'
		<< " / ___ | / ,<  /  __// /  		" << '\n'
		<< "/_/  |_|/_/|_| \\___//_/  		" << '\n'
    	<< "By Malo DAVID - 2021" << std::endl;
	}

	void printEngineCodeInfo()
	{
		std::cout
		<< "Language : C++ (C++17)" << '\n'
		<< "Graphics : Vulkan, SDL_Image" << '\n'
		<< "Window : SDL2, ImGUI" << '\n'
		<< "Sounds : SDL_mixer" << std::endl;
	}
}
