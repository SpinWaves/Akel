// This file is a part of AtlasEngine
// CREATED : 19/04/2021
// UPDATED : 05/06/2021

#include <Core/core.h>

namespace AE::Core
{
    void printCPUinfo()
    {
        CPU cinfo;
        std::cout << "CPU vendor : " << cinfo.vendor() << std::endl;
        std::cout << "CPU Brand String : " << cinfo.model() << std::endl;
        std::cout << "Number of cores : " << cinfo.cores() << std::endl;
        std::cout << "Number of logical cores : " << cinfo.logicalCpus() << std::endl;
        std::cout << "Is CPU Hyper threaded : " << cinfo.isHyperThreaded() << std::endl;
        std::cout << "CPU SSE : " << cinfo.isSSE() << std::endl;
        std::cout << "CPU SSE2 : " << cinfo.isSSE2() << std::endl;
        std::cout << "CPU SSE3 : " << cinfo.isSSE3() << std::endl;
        std::cout << "CPU SSE41 : " << cinfo.isSSE41() << std::endl;
        std::cout << "CPU SSE42 : " << cinfo.isSSE42() << std::endl;
        std::cout << "CPU AVX : " << cinfo.isAVX() << std::endl;
        std::cout << "CPU AVX2 : " << cinfo.isAVX2() << std::endl;
    }

    void printGPUinfo()
    {
        GPU info;
        std::cout << "GPU vendor : " << info.getVendorName() << std::endl;
        std::cout << "GPU model : " << info.getModelName() << std::endl;
        std::cout << "Vulkan version : " << info.getVulkanVersion() << std::endl;
        std::cout << "Number devices : " << info.getNumberOfDevices() << std::endl;
    }
}
