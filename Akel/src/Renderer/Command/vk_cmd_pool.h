// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/04/2022
// Updated : 07/05/2022

#ifndef __AK_VK_CMD_POOL__
#define __AK_VK_CMD_POOL__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
	class CmdPool
	{
		public:
			void init();
			inline void destroy()
			{
				Ak_assert(_cmd_pool != VK_NULL_HANDLE, "trying to destroy an uninit command pool");
				vkDestroyCommandPool(Render_Core::get().getDevice().get(), _cmd_pool, nullptr);
			}

			inline VkCommandPool& operator()() noexcept { return _cmd_pool; }
			inline VkCommandPool& get() noexcept { return _cmd_pool; }

		private:
			VkCommandPool _cmd_pool = VK_NULL_HANDLE;
	};
}

#endif // __AK_VK_CMD_POOL__
