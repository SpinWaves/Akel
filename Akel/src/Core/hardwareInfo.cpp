// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/04/2021
// Updated : 05/01/2022

#include <Core/core.h>

namespace Ak::Core
{
    void printCPUinfo()
    {
        CPU cinfo;
        std::cout << "CPU vendor : " << cinfo.vendor() << '\n'
                  << "CPU Brand String : " << cinfo.model() << '\n'
                  << "Number of cores : " << cinfo.cores() << '\n'
                  << "Number of logical cores : " << cinfo.logicalCpus() << '\n'
                  << "Is CPU Hyper threaded : " << cinfo.isHyperThreaded() << '\n'
                  << "CPU SSE : " << cinfo.isSSE() << '\n'
                  << "CPU SSE2 : " << cinfo.isSSE2() << '\n'
                  << "CPU SSE3 : " << cinfo.isSSE3() << '\n'
                  << "CPU SSE41 : " << cinfo.isSSE41() << '\n'
                  << "CPU SSE42 : " << cinfo.isSSE42() << '\n'
                  << "CPU AVX : " << cinfo.isAVX() << '\n'
                  << "CPU AVX2 : " << cinfo.isAVX2() << std::endl;
    }

    void printGPUinfo()
    {
        GPU info;
        std::cout << "GPU vendor : " << info.getVendorName() << '\n'
                  << "GPU model : " << info.getModelName() << '\n'
                  << "Vulkan version : " << info.getVulkanVersion() << '\n'
                  << "Number devices : " << info.getNumberOfDevices() << std::endl;
    }
}
