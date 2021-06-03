// This file is a part of AtlasEngine
// CREATED : 23/04/2021
// UPDATED : 03/06/2021

#ifndef __AE_GPU__
#define __AE_GPU__

#include <AEpch.h>

namespace AE::Core
{
    class GPU
    {
        public:
            GPU();

            uint32_t getNumberOfDevices();
            std::string getModelName();
            std::string getVendorName();
            uint32_t getVulkanVersion();
            float getGLSLversion();
            float getOpenGLversion();

            ~GPU();

        private:
            std::vector<VkPhysicalDevice> _devices;
            uint32_t _deviceCount = 0;
            VkInstance _instance;
            VkPhysicalDeviceProperties _deviceProperties;
            bool useVulkan = false;
            SDL_Window* _tempoWin;
            SDL_GLContext _context;
            std::map<uint32_t, std::string> vendors;
    };
}

#endif // __AE_GPU__
