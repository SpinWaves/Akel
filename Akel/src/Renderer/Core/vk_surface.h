// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 08/05/2022

#ifndef __AK_VK_SURFACE__
#define __AK_VK_SURFACE__

#include <Akpch.h>

namespace Ak
{
	class Surface
	{
		public:
			void create();
			void destroy() noexcept;
			
			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

			inline VkSurfaceKHR& operator()() noexcept { return _surface; }
			inline VkSurfaceKHR& get() noexcept { return _surface; }

		private:
			VkSurfaceKHR _surface = VK_NULL_HANDLE;
	};
}

#endif // __AK_VK_SURFACE__
