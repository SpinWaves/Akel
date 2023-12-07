// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/04/2021
// Updated : 21/11/2023

#ifndef __AK_GPU__
#define __AK_GPU__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak::Core
{
    class AK_API GPU
    {
        public:
            GPU();

            inline uint32_t getNumberOfDevices() noexcept { return _deviceCount; }
            inline std::string getModelName() { return std::string(_deviceProperties.deviceName); }
            inline std::string getVendorName() { return _vendors[_deviceProperties.vendorID]; }
            inline std::string getDeviceType() { return _types[static_cast<int>(_deviceProperties.deviceType)]; }
            inline std::string getVulkanVersion()
            {
                std::string res = std::to_string(VK_VERSION_MAJOR(_instanceVersion));
                res.push_back('.');
                res.append(std::to_string(VK_VERSION_MINOR(_instanceVersion)));
                res.push_back('.');
                res.append(std::to_string(VK_VERSION_PATCH(_instanceVersion)));
                return res;
            }
            inline std::string getDriverVersion()
            {
                std::string res = std::to_string(VK_VERSION_MAJOR(_deviceProperties.driverVersion));
                res.push_back('.');
                res.append(std::to_string(VK_VERSION_MINOR(_deviceProperties.driverVersion)));
                res.push_back('.');
                res.append(std::to_string(VK_VERSION_PATCH(_deviceProperties.driverVersion)));
                return res;
            }

            ~GPU() = default;

        private:
            std::vector<VkPhysicalDevice> _devices;
            VkInstance _instance;
            VkPhysicalDeviceProperties _deviceProperties;
            std::map<uint32_t, std::string> _vendors;
            std::array<std::string, 5> _types;
            uint32_t _deviceCount = 0;
            uint32_t _instanceVersion = VK_API_VERSION_1_3;
    };
}

#endif // __AK_GPU__
