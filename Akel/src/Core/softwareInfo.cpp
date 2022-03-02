// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/04/2021
// Updated : 20/10/2021

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
		{
        	vkDestroyInstance(instance, nullptr);
            return true;
		}
        return false;
    }

    void printEngineInfo()
    {
        std::cout
		<< "    ___     __          __ 		" << '\n'
		<< "   /   |   / /__ ___   / /		" << '\n'
		<< "  / /| |  / //_// _ \\ / / 		" << '\n'
		<< " / ___ | / ,<  /  __// /  		" << '\n'
		<< "/_/  |_|/_/|_| \\___//_/  		" << '\n'
    	<< '\t' << '\t' << "By SpinWaves Studios - 2021-2022" << std::endl;
	}

	void printEngineCodeInfo()
	{
		std::cout
		<< "Language : C++ (C++17)" << '\n'
		<< "Graphics : Vulkan, SDL_Image, ImGui" << '\n'
		<< "Window : SDL2" << '\n'
		<< "Sounds : OpenAL, SNDfile" << std::endl;
	}
}
