// This file is a part of AtlasEngine
// CREATED : 05/04/2021
// UPDATED : 23/04/2021

#ifndef __SOFTWARE_INFO__
#define __SOFTWARE_INFO__

#include <AEpch.h>

namespace AE::Core
{
        std::string getGLinfo();
        std::string getGLSLinfo();
        bool isVulkanSupported();
}

#endif // __SOFTWARE_INFO__
