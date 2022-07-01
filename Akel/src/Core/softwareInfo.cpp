// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/04/2021
// Updated : 13/06/2022

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
}
