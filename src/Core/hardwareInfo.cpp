// This file is a part of AtlasEngine
// CREATED : 19/04/2021
// UPDATED : 20/04/2021

#include <Core/core.h>

namespace AE::Core
{
    std::string HardInfo::getCPUinfo()
    {
        int infotype, a, b, c, d;

        #if defined(__clang__) || defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW34__)
            for (infotype = 0; infotype < 5; infotype ++)
            {
                __asm__
                (
                    #include "CPUID_GCC.asm"
                );
                printf("InfoType %x\nEAX: %x\nEBX: %x\nECX: %x\nEDX: %x\n", infotype, a, b, c, d);
            }
        #elif defined(_MSC_VER) || defined(__BORLANDC__)
            __asm
            {
                #include "CPUID_MSVC.asm"
            }
            printf("InfoType %x\nEAX: %x\nEBX: %x\nECX: %x\nEDX: %x\n", infotype, a, b, c, d);
        #endif
    }
}
