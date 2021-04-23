// This file is a part of AtlasEngine
// CREATED : 23/04/2021
// UPDATED : 23/04/2021

#ifndef __GPU__
#define __GPU__

#include <AEpch.h>

namespace AE::Core
{
    class GPU
    {
        public:
            GPU();

            uint8_t getNumberOfDevices();
            std::string getModelName();

            ~GPU();

        private:
            std::vector<VkPhysicalDevice> _devices;
            uint32_t _deviceCount = 0;
            VkInstance _instance;
            VkPhysicalDeviceProperties _deviceProperties;
            bool useVulkan;
            SDL_Window* _tempoWin;
            SDL_GLContext _context;
    };
}

#endif // __GPU__
