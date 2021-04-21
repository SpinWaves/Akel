// This file is a part of AtlasEngine
// CREATED : 19/04/2021
// UPDATED : 21/04/2021

#include <Core/core.h>

namespace AE::Core
{
    void CopyRegToBuff(uint32_t Reg, char* Buff)
    {
        for (int i = 0; i < 4; i++)
        {
            Buff[i] = Reg & 0xFF;
            Reg >>= 8;
        }		
    }

    //Calls CPUID subfunction 0 to retrieve vendor ID string in ebx, edx, ecx.
    std::string GetVendorID(uint32_t ebx, uint32_t ecx, uint32_t edx)
    {
        char VendorID[13];
        memset(VendorID, 0, sizeof(VendorID));
        CopyRegToBuff(ebx, VendorID);
        CopyRegToBuff(edx, VendorID + 4);
        CopyRegToBuff(ecx, VendorID + 8);
        
        return std::string(VendorID); 
    }


    std::string HardInfo::getCPUinfo()
    {
        CPUInfo cinfo;
        std::cout << "CPU vendor = " << cinfo.vendor() << std::endl;
        std::cout << "CPU Brand String = " << cinfo.model() << std::endl;
        std::cout << "# of cores = " << cinfo.cores() << std::endl;
        std::cout << "# of logical cores = " << cinfo.logicalCpus() << std::endl;
        std::cout << "Is CPU Hyper threaded = " << cinfo.isHyperThreaded() << std::endl;
        std::cout << "CPU SSE = " << cinfo.isSSE() << std::endl;
        std::cout << "CPU SSE2 = " << cinfo.isSSE2() << std::endl;
        std::cout << "CPU SSE3 = " << cinfo.isSSE3() << std::endl;
        std::cout << "CPU SSE41 = " << cinfo.isSSE41() << std::endl;
        std::cout << "CPU SSE42 = " << cinfo.isSSE42() << std::endl;
        std::cout << "CPU AVX = " << cinfo.isAVX() << std::endl;
        std::cout << "CPU AVX2 = " << cinfo.isAVX2() << std::endl;
    }
}
