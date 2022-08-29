// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/04/2021
// Updated : 30/08/2022

#ifndef __AK_CPU__
#define __AK_CPU__

#include <Akpch.h>

namespace Ak::Core
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

            inline std::string vendor() const { return _VendorId; }
            inline std::string model() const { return _ModelName; }
            inline int cores() const noexcept { return _NumCores; }
            inline float cpuSpeedInMHz() const noexcept { return _CPUMHz; }
            inline bool isSSE() const noexcept { return _IsSSE; }
			inline bool isSSE2() const noexcept { return _IsSSE2; }
			inline bool isSSE3() const noexcept { return _IsSSE3; }
			inline bool isSSE41() const noexcept { return _IsSSE41; }
			inline bool isSSE42() const noexcept { return _IsSSE42; }
			inline bool isAVX() const noexcept { return _IsAVX; }
			inline bool isAVX2() const noexcept { return _IsAVX2; }
			inline bool isHyperThreaded() const noexcept { return _IsHTT; }
            inline int logicalCpus() const noexcept { return _NumLogCpus; }

        private:
            // Bit positions for data extractions
            constexpr static const uint32_t SSE_POS   = 0x02000000;
            constexpr static const uint32_t SSE2_POS  = 0x04000000;
        	constexpr static const uint32_t SSE3_POS  = 0x00000001;
			constexpr static const uint32_t SSE41_POS = 0x00080000;
			constexpr static const uint32_t SSE42_POS = 0x00100000;
			constexpr static const uint32_t AVX_POS   = 0x10000000;
			constexpr static const uint32_t AVX2_POS  = 0x00000020;
			constexpr static const uint32_t LVL_NUM   = 0x000000FF;
			constexpr static const uint32_t LVL_TYPE  = 0x0000FF00;
			constexpr static const uint32_t LVL_CORES = 0x0000FFFF;

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

#endif // __AK_CPU__
