// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2022
// Updated : 27/03/2022

#include "commandBuffer.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
	CommandBuffer::CommandBuffer(bool begin, VkQueueFlagBits queueType, VkCommandBufferLevel bufferLevel) : _commandPool(Graphics::Get()->GetCommandPool()), _queueType(queueType)
	{
		auto logicalDevice = Render_Core::get().getLogicalDevice();

		VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.commandPool = *_commandPool;
		commandBufferAllocateInfo.level = bufferLevel;
		commandBufferAllocateInfo.commandBufferCount = 1;
		RCore::checkVk(vkAllocateCommandBuffers(*logicalDevice, &commandBufferAllocateInfo, &_commandBuffer));

		if(begin)
			beginRecord();
	}

	void CommandBuffer::beginRecord(VkCommandBufferUsageFlags usage)
	{
		if(_is_recording)
			return;

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = usage;
		RCore::checkVk(vkBeginCommandBuffer(_commandBuffer, &beginInfo));
		_is_recording = true;
	}

	void CommandBuffer::endRecord()
	{
		if(!_is_recording)
			return;

		RCore::checkVk(vkEndCommandBuffer(_commandBuffer));
		_is_recording = false;
	}

	void CommandBuffer::passIdle()
	{
		auto logicalDevice = Render_Core::get().getLogicalDevice();
		auto queueSelected = getQueue();

		if(_is_recording)
			endRecord();

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &_commandBuffer;

		VkFenceCreateInfo fenceCreateInfo{};
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

		VkFence fence;
		RCore::checkVk(vkCreateFence(*logicalDevice, &fenceCreateInfo, nullptr, &fence));
		RCore::checkVk(vkResetFences(*logicalDevice, 1, &fence));
		RCore::checkVk(vkQueueSubmit(queueSelected, 1, &submitInfo, fence));
		RCore::checkVk(vkWaitForFences(*logicalDevice, 1, &fence, VK_TRUE, std::numeric_limits<uint64_t>::max()));

		vkDestroyFence(*logicalDevice, fence, nullptr);
	}

	void CommandBuffer::pass(const VkSemaphore& waitSemaphore, const VkSemaphore& signalSemaphore, VkFence fence)
	{
		auto logicalDevice = Render_Core::get().getLogicalDevice();
		auto queueSelected = getQueue();

		if(_is_recording)
			endRecord();

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &_commandBuffer;

		if(waitSemaphore != VK_NULL_HANDLE)
		{
			static VkPipelineStageFlags submitPipelineStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

			submitInfo.pWaitDstStageMask = &submitPipelineStages;
			submitInfo.waitSemaphoreCount = 1;
			submitInfo.pWaitSemaphores = &waitSemaphore;
		}

		if(signalSemaphore != VK_NULL_HANDLE)
		{
			submitInfo.signalSemaphoreCount = 1;
			submitInfo.pSignalSemaphores = &signalSemaphore;
		}

		if(fence != VK_NULL_HANDLE)
			RCore::checkVk(vkResetFences(*logicalDevice, 1, &fence));

		RCore::checkVk(vkQueueSubmit(queueSelected, 1, &submitInfo, fence));
	}

	VkQueue CommandBuffer::getQueue() const
	{
		auto logicalDevice = Render_Core::get().getLogicalDevice();

		switch(queueType)
		{
			case VK_QUEUE_GRAPHICS_BIT: return logicalDevice->getGraphicsQueue();
			case VK_QUEUE_COMPUTE_BIT: return logicalDevice->getComputeQueue();
			default: return nullptr;
		}
	}

	CommandBuffer::~CommandBuffer()
	{
		auto logicalDevice = Render_Core::get().getLogicalDevice();
		vkFreeCommandBuffers(*logicalDevice, _commandPool->getCommandPool(), 1, &_commandBuffer);
	}
}
