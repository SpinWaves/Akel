// This file is a part of AtlasEngine
// CREATED : 05/06/2021
// UPDATED : 05/06/2021

#ifndef __AE_VK_RENDER_PASS__
#define __AE_VK_RENDER_PASS__

#include <AEpch.h>

#include <Renderer/lowestInheritance.h>

namespace AE
{
	class RenderPass : virtual public LowestInheritance
	{
		public:
			RenderPass();
            void createRenderPass();

            VkRenderPass renderPass;
	};
}

#endif // __AE_VK_RENDER_PASS__

