// This file is a part of AtlasEngine
// CREATED : 05/04/2021
// UPDATED : 16/04/2021

#include <Core/core.h>

namespace AE::Core
{
    std::string SoftInfo::getGLinfo()
    {
        return std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    }
    std::string SoftInfo::getGLSLinfo()
    {
        return std::string(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
    }
}
