// This file is a part of AtlasEngine
// CREATED : 05/06/2021
// UPDATED : 05/06/2021

#ifndef __AE_VK_SURFACE__
#define __AE_VK_SURFACE__

#include <AEpch.h>

#include <Renderer/lowestInheritance.h>

namespace AE
{
	class Surface : virtual public LowestInheritance
	{
		public:
			Surface();

            void createSurface();
            VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	};
}

#endif // __AE_VK_SURFACE__

