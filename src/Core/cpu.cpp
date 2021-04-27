// This file is a part of AtlasEngine
// CREATED : 21/04/2021
// UPDATED : 27/04/2021

#include <Core/core.h>
#include <Platform/platform.h>

#define MAX_INTEL_TOP_LVL 4

namespace AE::Core
{
    CPUID::CPUID(unsigned funcId, unsigned subFuncId)
    {
        #if defined(__clang__) || defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW34__)
            __asm__
            (
                #include "CPUID_GCC.inline-asm"
            );
        #else   // MSVC or BORLANDC
            __asm
            {
                #include "CPUID_MSVC.inline-asm"
            }
        #endif
    }

    uint32_t& CPUID::EAX() 
    {
        return regs[0];
    }
    uint32_t& CPUID::EBX() 
    {
        return regs[1];
    }
    uint32_t& CPUID::ECX() 
    {
        return regs[2];
    }
    uint32_t& CPUID::EDX() 
    {
        return regs[3];
    }


    CPUInfo::CPUInfo()
    {
        CPUID cpuID0(0, 0);
        uint32_t HFS = cpuID0.EAX();
        _VendorId += std::string((const char*)&cpuID0.EBX(), 4);
        _VendorId += std::string((const char*)&cpuID0.EDX(), 4);
        _VendorId += std::string((const char*)&cpuID0.ECX(), 4);

        CPUID cpuID1(1, 0);
        _IsHTT = cpuID1.EDX() & AVX_POS;
        _IsSSE = cpuID1.EDX() & SSE_POS;
        _IsSSE2 = cpuID1.EDX() & SSE2_POS;
        _IsSSE3 = cpuID1.ECX() & SSE3_POS;
        _IsSSE41 = cpuID1.ECX() & SSE41_POS;
        _IsSSE42 = cpuID1.ECX() & SSE41_POS;
        _IsAVX = cpuID1.ECX() & AVX_POS;

        CPUID cpuID7(7, 0);
        _IsAVX2 = cpuID7.EBX() & AVX2_POS;

        std::string upVId = _VendorId;
        for_each(upVId.begin(), upVId.end(), [](char& in) { in = ::toupper(in); });

        if(upVId.find("INTEL") != std::string::npos)
        {
            if(HFS >= 11)
            {
                for (int lvl = 0; lvl < MAX_INTEL_TOP_LVL; lvl++)
                {
                        CPUID cpuID4(0x0B, lvl);
                        uint32_t currLevel = (LVL_TYPE & cpuID4.ECX()) >> 8;

                        switch(currLevel) 
                        {
                            case 0x01: _NumSMT = LVL_CORES & cpuID4.EBX(); break;
                            case 0x02: _NumLogCpus = LVL_CORES & cpuID4.EBX(); break;

                            default: break;
                        }
                }
                _NumCores = _NumLogCpus/_NumSMT;
            } 
            else
            {
                if(HFS >= 1)
                {
                    _NumLogCpus = (cpuID1.EBX() >> 16) & 0xFF;
                    if(HFS>=4)
                        _NumCores = 1 + (CPUID(4, 0).EAX() >> 26) & 0x3F;
                }
                if(_IsHTT) 
                {
                    if(!(_NumCores > 1)) 
                    {
                        _NumCores = 1;
                        _NumLogCpus = (_NumLogCpus >= 2 ? _NumLogCpus : 2);
                    }
                } 
                else
                    _NumCores = _NumLogCpus = 1;
            }
        } 
        else if(upVId.find("AMD") != std::string::npos) 
        {
            if(HFS>=1)
            {
                _NumLogCpus = (cpuID1.EBX() >> 16) & 0xFF;
                if (CPUID(0x80000000, 0).EAX() >=8)
                    _NumCores = 1 + (CPUID(0x80000008, 0).ECX() & 0xFF);
            }
            if(_IsHTT)
            {
                if(!(_NumCores > 1)) 
                {
                    _NumCores = 1;
                    _NumLogCpus = (_NumLogCpus >= 2 ? _NumLogCpus : 2);
                }
            }
            else
                _NumCores = _NumLogCpus = 1;
        } 
        else
            messageBox(ERROR, "Unable to get CPU info", AE_CATCH_CPU_VENDOR_INFO);

        for(int i = 0x80000002; i < 0x80000005; i++)
        {
            CPUID cpuID(i, 0);
            _ModelName += std::string((const char*)&cpuID.EAX(), 4);
            _ModelName += std::string((const char*)&cpuID.EBX(), 4);
            _ModelName += std::string((const char*)&cpuID.ECX(), 4);
            _ModelName += std::string((const char*)&cpuID.EDX(), 4);
        }
    
    }

    std::string CPUInfo::vendor() 
    { 
        return _VendorId;
    }
    std::string CPUInfo::model()
    { 
        return _ModelName;
    }
    int CPUInfo::cores()
    { 
        return _NumCores;   
    }
    float CPUInfo::cpuSpeedInMHz()      
    { 
        return _CPUMHz;     
    }
    bool CPUInfo::isSSE()              
    { 
        return _IsSSE;      
    }
    bool CPUInfo::isSSE2()             
    { 
        return _IsSSE2;     
    }
    bool CPUInfo::isSSE3()             
    { 
        return _IsSSE3;     
    }
    bool CPUInfo::isSSE41()            
    { 
        return _IsSSE41;   
    }
    bool CPUInfo::isSSE42()            
    { 
        return _IsSSE42;    
    }
    bool CPUInfo::isAVX()              
    { 
        return _IsAVX;     
    }
    bool CPUInfo::isAVX2()             
    { 
        return _IsAVX2;     
    }
    bool CPUInfo::isHyperThreaded()    
    { 
        return _IsHTT;      
    }
    int CPUInfo::logicalCpus()        
    { 
        return _NumLogCpus; 
    }
}
