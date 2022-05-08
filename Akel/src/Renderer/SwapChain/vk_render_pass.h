// this file is a part of akel
// authors : @kbz_8
// created : 10/04/2022
// updated : 08/05/2022

#ifndef __AK_VK_RENDER_PASS__
#define __AK_VK_RENDER_PASS__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
	class RenderPass
	{
		public:
			void init();
			void destroy() noexcept;

			void begin();
			void end();
			
            inline VkRenderPass& operator()() noexcept { return _renderPass; }
            inline VkRenderPass& get() noexcept { return _renderPass; }

		private:
			VkRenderPass _renderPass = VK_NULL_HANDLE;
			bool _is_running = false;
	};
}

#endif // __AK_VK_RENDER_PASS__
