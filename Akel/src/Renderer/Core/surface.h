// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2022
// Updated : 27/03/2022

#ifndef __AK_VK_SURFACE__
#define __AK_VK_SURFACE__

#include <Akpch.h>

namespace Ak
{
	class Instance;
	class PhysicalDevice;

	class Surface
	{
		public:
			Surface(const Instance* instance, const PhysicalDevice* physicalDevice);

			inline operator const VkSurfaceKHR& () const { return _surface; }

			inline const VkSurfaceKHR& getSurface() const noexcept { return _surface; }
			inline const VkSurfaceCapabilitiesKHR& getCapabilities() const noexcept { return _capabilities; }
			inline const VkSurfaceFormatKHR& getFormat() const noexcept { return _format; }

			~Surface();

		private:
			const Instance* _instance;
			const PhysicalDevice* _physicalDevice;

			VkSurfaceKHR _surface = VK_NULL_HANDLE;
			VkSurfaceCapabilitiesKHR _capabilities = {};
			VkSurfaceFormatKHR _format = {};
	};
}

#endif // __AK_VK_SURFACE__
