// this file is a part of akel
// authors : @kbz_8
// created : 10/04/2022
// updated : 11/04/2022

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

			inline void destroy() noexcept
			{
				static_assert(_renderPass != VK_NULL_HANDLE, "trying to destroy an uninit render pass");
				vkDestroyRenderPass(Render_Core::get().getDevice().get(), _renderPass, nullptr);
			}

			void begin();
			void end();
			
            inline VkRenderPass& operator()() const noexcept { return _renderPass; }
            inline VkRenderPass& get() const noexcept { return _renderPass; }

		private:
			VkRenderPass _renderPass = VK_NULL_HANDLE;
			bool _is_running = false;
	};
}

#endif // __AK_VK_RENDER_PASS__
