// This file is a part of Akel
// CREATED : 05/06/2021
// UPDATED : 05/06/2021

#ifndef __AK_VK_RENDER_PASS__
#define __AK_VK_RENDER_PASS__

#include <Akpch.h>

#include <Renderer/lowestInheritance.h>

namespace Ak
{
	class RenderPass : virtual public LowestInheritance
	{
		public:
			RenderPass();
            void createRenderPass();

            VkRenderPass renderPass;
	};
}

#endif // __AK_VK_RENDER_PASS__

