// This file is a part of Akel
// CREATED : 05/06/2021
// UPDATED : 05/06/2021

#ifndef __AK_VK_SURFACE__
#define __AK_VK_SURFACE__

#include <Akpch.h>

#include <Renderer/lowestInheritance.h>

namespace Ak
{
	class Surface : virtual public LowestInheritance
	{
		public:
			Surface();

            void createSurface();
            VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	};
}

#endif // __AK_VK_SURFACE__

