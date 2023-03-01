// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/03/2023
// Updated : 01/03/2023

#include <Renderer/Core/vk_fence.h>
#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>

namespace Ak
{
	void Fence::init()
	{
		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			if(vkCreateFence(Render_Core::get().getDevice().get(), &fenceInfo, nullptr, &_fences[i]) != VK_SUCCESS)
				Core::log::report(FATAL_ERROR, "Vulkan : failed to create CPU synchronization objects for a frame");
		}
	}

	void Fence::destroy() noexcept
	{
		for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			Ak_assert(_fences[i] != VK_NULL_HANDLE, "trying to destroy an uninit fence");
			vkDestroyFence(Render_Core::get().getDevice().get(), _fences[i], nullptr);
		}
	}
}
