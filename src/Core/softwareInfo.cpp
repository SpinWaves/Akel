// This file is a part of AtlasEngine
// CREATED : 05/04/2021
// UPDATED : 23/04/2021

#include <Core/core.h>

namespace AE::Core
{
    std::string getGLinfo()
    {
        return std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    }
    std::string getGLSLinfo()
    {
        return std::string(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
    }

    bool isVulkanSupported()
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        if(extensionCount != 0)
            return true;
        return false;
    }
}
