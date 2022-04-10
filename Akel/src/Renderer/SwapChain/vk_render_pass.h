// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 10/04/2022

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
			
            inline VkRenderPass& operator()() const noexcept { return _renderPass; }
            inline VkRenderPass& get() const noexcept { return _renderPass; }

		private:
			VkRenderPass _renderPass = VK_NULL_HANDLE;
	};
}

#endif // __AK_VK_RENDER_PASS__
