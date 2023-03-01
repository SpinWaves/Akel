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

		if(vkCreateFence(Render_Core::get().getDevice().get(), &fenceInfo, nullptr, &_fence) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create CPU synchronization objects for a frame");
	}

	void Fence::wait() noexcept
	{
		vkWaitForFences(Render_Core::get().getDevice().get(), 1, &_fence, VK_TRUE, UINT64_MAX);
	}

	void Fence::reset() noexcept
	{
		vkResetFences(Render_Core::get().getDevice().get(), 1, &_fence);
	}

	void Fence::destroy() noexcept
	{
		Ak_assert(_fence != VK_NULL_HANDLE, "trying to destroy an uninit fence");
		vkDestroyFence(Render_Core::get().getDevice().get(), _fence, nullptr);
	}
}
