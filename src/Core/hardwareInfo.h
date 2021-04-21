// This file is a part of AtlasEngine
// CREATED : 19/04/2021
// UPDATED : 21/04/2021

#ifndef __HARDWARE_INFO__
#define __HARDWARE_INFO__

#include <AEpch.h>

namespace AE::Core
{
    class HardInfo
    {
        public:
            static std::string getCPUinfo();
    };
}

#endif // __HARDWARE_INFO__