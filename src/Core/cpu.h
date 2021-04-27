// This file is a part of AtlasEngine
// CREATED : 21/04/2021
// UPDATED : 27/04/2021

#ifndef __CPU__
#define __CPU__

#include <AEpch.h>

namespace AE::Core
{
    class CPUID 
    {
        public:
            CPUID(unsigned funcId, unsigned subFuncId);

            uint32_t &EAX();
            uint32_t &EBX();
            uint32_t &ECX();
            uint32_t &EDX();
        
        private:
            uint32_t regs[4];
    };

    class CPU
    {
        public:
            CPU();

            std::string vendor();
            std::string model();
            int cores();
            float cpuSpeedInMHz();
            bool isSSE();
            bool isSSE2();
            bool isSSE3();
            bool isSSE41();
            bool isSSE42();
            bool isAVX();
            bool isAVX2();
            bool isHyperThreaded();
            int logicalCpus();

        private:
            // Bit positions for data extractions
            static const uint32_t SSE_POS   = 0x02000000;
            static const uint32_t SSE2_POS  = 0x04000000;
            static const uint32_t SSE3_POS  = 0x00000001;
            static const uint32_t SSE41_POS = 0x00080000;
            static const uint32_t SSE42_POS = 0x00100000;
            static const uint32_t AVX_POS   = 0x10000000;
            static const uint32_t AVX2_POS  = 0x00000020;
            static const uint32_t LVL_NUM   = 0x000000FF;
            static const uint32_t LVL_TYPE  = 0x0000FF00;
            static const uint32_t LVL_CORES = 0x0000FFFF;

            std::string _VendorId;
            std::string _ModelName;
            int _NumSMT;
            int _NumCores;
            int _NumLogCpus;
            float _CPUMHz;
            bool _IsHTT;
            bool _IsSSE;
            bool _IsSSE2;
            bool _IsSSE3;
            bool _IsSSE41;
            bool _IsSSE42;
            bool _IsAVX;
            bool _IsAVX2;
    };
}

#endif // __CPU__
