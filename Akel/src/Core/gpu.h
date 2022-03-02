// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/04/2021
// Updated : 05/06/2021

#ifndef __AK_GPU__
#define __AK_GPU__

#include <Akpch.h>

namespace Ak::Core
{
    class GPU
    {
        public:
            GPU();

            uint32_t getNumberOfDevices();
            std::string getModelName();
            std::string getVendorName();
            uint32_t getVulkanVersion();

            ~GPU();

        private:
            std::vector<VkPhysicalDevice> _devices;
            uint32_t _deviceCount = 0;
            VkInstance _instance;
            VkPhysicalDeviceProperties _deviceProperties;
            std::map<uint32_t, std::string> vendors;
    };
}

#endif // __AK_GPU__
