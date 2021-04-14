// This file is a part of AtlasEngine
// CREATED : 05/04/2021
// UPDATED : 14/04/2021

#include <Core/core.h>

namespace AE::Core
{
    std::string SoftInfo::getGLinfo()
    {
        return std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    }
}
