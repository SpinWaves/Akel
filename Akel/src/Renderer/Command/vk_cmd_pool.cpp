// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/04/2022
// Updated : 31/05/2022

#include "vk_cmd_pool.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
	void CmdPool::init()
	{
		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex = Render_Core::get().getQueue().findQueueFamilies(Render_Core::get().getDevice().getPhysicalDevice()).graphicsFamily.value();

		if(vkCreateCommandPool(Render_Core::get().getDevice().get(), &poolInfo, nullptr, &_cmd_pool) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create command pool");
	}

	void CmdPool::destroy() noexcept
	{
		Ak_assert(_cmd_pool != VK_NULL_HANDLE, "trying to destroy an uninit command pool");
		vkDestroyCommandPool(Render_Core::get().getDevice().get(), _cmd_pool, nullptr);
	}
}
