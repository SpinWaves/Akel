// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/04/2021
// Updated : 22/12/2022

#include <Core/softwareInfo.h>

namespace Ak::Core
{
    bool isVulkanSupported()
    {
		uint32_t ver;
		volkInitialize();
        if(vkEnumerateInstanceVersion(&ver) == VK_SUCCESS)
			return true;
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
