// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/04/2022
// Updated : 17/06/2023

#include <Renderer/Command/vk_cmd_buffer.h>
#include <Renderer/Command/cmd_manager.h>
#include <Renderer/Core/render_core.h>
#include <Renderer/Core/vk_semaphore.h>
#include <Utils/assert.h>

namespace Ak
{
	void CmdBuffer::init(CmdManager& manager, bool is_single_time)
	{
		_is_single_time = is_single_time;
		_pool = &manager.getCmdPool();

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = manager.getCmdPool().get();
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = 1;

		if(vkAllocateCommandBuffers(Render_Core::get().getDevice().get(), &allocInfo, &_cmd_buffer) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to allocate command buffer");

		_fence.init();
	}

	void CmdBuffer::init(CmdPool* pool, bool is_single_time)
	{
		_is_single_time = is_single_time;
		_pool = pool;

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = pool->get();
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = 1;

		if(vkAllocateCommandBuffers(Render_Core::get().getDevice().get(), &allocInfo, &_cmd_buffer) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to allocate command buffer");

		_fence.init();
	}

	void CmdBuffer::beginRecord(VkCommandBufferUsageFlags usage)
	{
		if(_is_recording)
			return;

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = usage;
		if(vkBeginCommandBuffer(_cmd_buffer, &beginInfo) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to begin recording command buffer");

		_is_recording = true;
	}

	void CmdBuffer::submit(Semaphore& semaphores) noexcept
	{
		if(_is_single_time)
		{
			Core::log::report(ERROR, "Vulkan : single time command buffers can only be submitted in idle mode, (using `submitIdle()`)");
			return;
		}
		VkSemaphore signalSemaphores[] = { semaphores.getRenderImageSemaphore() };
		VkSemaphore waitSemaphores[] = { semaphores.getImageSemaphore() };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &_cmd_buffer;
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		if(vkQueueSubmit(Render_Core::get().getQueue().getGraphic(), 1, &submitInfo, _fence.get()) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan error : failed to submit draw command buffer");
	}

	void CmdBuffer::submitIdle()
	{
		auto device = Render_Core::get().getDevice().get();

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &_cmd_buffer;

		VkFenceCreateInfo fenceCreateInfo = {};
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

		VkFence fence;
		vkCreateFence(device, &fenceCreateInfo, nullptr, &fence);
		vkResetFences(device, 1, &fence);
		vkQueueSubmit(Render_Core::get().getQueue().getGraphic(), 1, &submitInfo, fence);
		vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);
		vkDestroyFence(device, fence, nullptr);
	}

	void CmdBuffer::endRecord()
	{
		if(!_is_recording)
			return;
		if(vkEndCommandBuffer(_cmd_buffer) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to end recording command buffer");

		_is_recording = false;
	}

	void CmdBuffer::destroy() noexcept
	{
		Ak_assert(_cmd_buffer != VK_NULL_HANDLE, "trying to destroy an uninit command buffer");
		vkFreeCommandBuffers(Render_Core::get().getDevice().get(), _pool->get(), 1, &_cmd_buffer);
		_cmd_buffer = VK_NULL_HANDLE;
		_fence.destroy();
	}
}
