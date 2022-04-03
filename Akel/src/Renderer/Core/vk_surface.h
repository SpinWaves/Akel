// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 03/04/2022

#ifndef __AK_VK_SURFACE__
#define __AK_VK_SURFACE__

#include <Akpch.h>
#include "render_core.h"

namespace Ak
{
	class Surface
	{
		public:
			void create();
			inline void destroy() noexcept { vkDestroySurfaceKHR(Render_Core::get().getInstance()->get(), _surface, nullptr); }
			
			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

			inline VkSurfaceKHR& operator()() const noexcept { return _surface; }
			inline VkSurfaceKHR& get() const noexcept { return _surface; }

		private:
			VkSurfaceKHR _surface;
	};
}

#endif // __AK_VK_SURFACE__
