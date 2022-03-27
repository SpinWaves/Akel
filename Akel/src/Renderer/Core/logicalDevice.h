// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2022
// Updated : 27/03/2022

#ifndef __AK_VK_LOGICAL_DEVICE__
#define __AK_VK_LOGICAL_DEVICE__

#include <Akpch.h>

namespace Ak
{
	class Instance;
	class PhysicalDevice;
	class Surface;

	// Represents a vulkan logical device
	class LogicalDevice
	{
		public:
			LogicalDevice(const Instance* instance, const PhysicalDevice* physicalDevice, const Surface* surface);

			inline operator const VkDevice& () const { return _logicalDevice; }

			inline const VkDevice& getLogicalDevice() const noexcept { return _logicalDevice; }
			inline const VkPhysicalDeviceFeatures& getEnabledFeatures() const noexcept { return _enabledFeatures; }
			inline const VkQueue& getGraphicsQueue() const noexcept { return _graphicsQueue; }
			inline const VkQueue& getPresentQueue() const noexcept { return _presentQueue; }
			inline const VkQueue& getComputeQueue() const noexcept { return _computeQueue; }
			inline const VkQueue& getTransferQueue() const noexcept { return _transferQueue; }
			inline uint32_t getGraphicsFamily() const noexcept { return _graphicsFamily; }
			inline uint32_t getPresentFamily() const noexcept { return _presentFamily; }
			inline uint32_t getComputeFamily() const noexcept { return _computeFamily; }
			inline uint32_t getTransferFamily() const noexcept { return _transferFamily; }

			static const std::vector<const char*> deviceExtensions;

			~LogicalDevice();

		private:
			void createQueueIndices();
			void createLogicalDevice();

			const Instance* _instance;
			const PhysicalDevice* _physicalDevice;
			const Surface* _surface;

			VkDevice _logicalDevice = VK_NULL_HANDLE;
			VkPhysicalDeviceFeatures _enabledFeatures = {};

			VkQueueFlags _supportedQueues = {};
			uint32_t _graphicsFamily = 0;
			uint32_t _presentFamily  = 0;
			uint32_t _computeFamily  = 0;
			uint32_t _transferFamily = 0;

			VkQueue _graphicsQueue = VK_NULL_HANDLE;
			VkQueue _presentQueue  = VK_NULL_HANDLE;
			VkQueue _computeQueue  = VK_NULL_HANDLE;
			VkQueue _transferQueue = VK_NULL_HANDLE;
	};
}

#endif // __AK_VK_LOGICAL_DEVICE__
