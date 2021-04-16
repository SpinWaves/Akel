// This file is a part of AtlasEngine
// CREATED : 05/04/2021
// UPDATED : 16/04/2021

#ifndef __SOFTWARE_INFO__
#define __SOFTWARE_INFO__

#include <AEpch.h>

namespace AE::Core
{
    class SoftInfo
    {
        public:
            static std::string getGLinfo();
            static std::string getGLSLinfo();
    };
}

#endif // __SOFTWARE_INFO__
