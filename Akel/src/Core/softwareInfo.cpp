// This file is a part of Akel
// CREATED : 05/04/2021
// UPDATED : 30/04/2021

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
        std::cout  << bold
		<< "          _   _           ______             _             "		 << std::endl
        << "     /\\  | | | |         |  ____|           (_)            "		 << std::endl
        << "    /  \\ | |_| | __ _ ___| |__   _ __   __ _ _ _ __   ___  "		 << std::endl
        << "   / /\\ \\| __| |/ _` / __|  __| | '_ \\ / _` | | '_ \\ / _ \\ "	 << std::endl
        << "  / ____ \\ |_| | (_| \\__ \\ |____| | | | (_| | | | | |  __/ "		 << std::endl
        << " /_/    \\_\\__|_|\\__,_|___/______|_| |_|\\__, |_|_| |_|\\___| "	 << std::endl
        << "                                        __/ |              "		 << std::endl
        << "                                       |___/               "		 << std::endl
    	<< "By Malo DAVID - 2021" 												 << std::endl
		<< "AtlasEngine is a game engine made for fun by a young french man in his bedroom" << std::endl
		<< "Its name was inspired by Sithis who is also known as Akel from The Elder Scrolls series" << bold_off << std::endl;
	}

	void printEngineCodeInfo()
	{
		std::cout
		<< "Language : C++ (C++17)" << std::endl
		<< "Graphics : Vulkan, OpenGL" << std::endl
		<< "Window : SDL2" << std::endl
		<< "Sounds : SDL_mixer" << std::endl;
	}
}
