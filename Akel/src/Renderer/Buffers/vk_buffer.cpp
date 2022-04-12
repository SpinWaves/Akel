// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 12/04/2022

#include "vk_buffer.h"

namespace Ak
{
	void Buffer::create(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags flags, const void* data)
	{
		_usage = usage;
		_flags = flags;
		_mem_chunck.size = size;

		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = _mem_chunck.size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		auto device = Render_Core::get().getDevice().get();

		if(vkCreateBuffer(device, &bufferInfo, nullptr, &_buffer) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create buffer");

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(device, _buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

		_mem_chunck = Render_Core::get().allocChunck(memRequirements, flags);

		if(data != nulptr)
		{
			void* mapped = nullptr;
			mapMemory(&mapped);
			std::memcpy(mapped, data, _mem_chunck.size);

			if((properties & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0)
			{
				VkMappedMemoryRange mappedMemoryRange = {};
				mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
				mappedMemoryRange.memory = _mem_chunck.memory;
				mappedMemoryRange.offset = _mem_chunck.offset;
				mappedMemoryRange.size = _mem_chunck.size;
				vkFlushMappedMemoryRanges(device, 1, &mappedMemoryRange);
			}

			unmapMemory();
		}

		vkBindBufferMemory(device, _buffer, _mem_chunck.memory, _mem_chunck.offset);
	}

	void Buffer::storeInGPU()
	{
		Buffer newBuffer;
		newBuffer.create(_usage, flags);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = Render_Core::get().getCommandPool().get();
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(Render_Core::get().getDevice().get(), &allocInfo, &commandBuffer);

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		VkBufferCopy copyRegion{};
		copyRegion.size = _size;
		vkCmdCopyBuffer(commandBuffer, _buffer, newBuffer._buffer, 1, &copyRegion);

		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(graphicsQueue);

		vkFreeCommandBuffers(Render_Core::get().getDevice().get(), Render_Core::get().getCmdPool().get(), 1, &commandBuffer);

		this->swap(newBuffer);

		newBuffer.destroy();
	}

	void Buffer::swap(Buffer& buffer)
	{
		VkBuffer temp_b = _buffer;
		_buffer = buffer._buffer;
		buffer._buffer = temp_b;

		GPU_Mem_Chunk temp_c = _mem_chunck;
		_mem_chunck = buffer._mem_chunck;
		buffer._mem_chunck = temp_c;

		VkBufferUsageFlags temp_u = _usage;
		_usage = buffer._usage;
		buffer._usage = temp_u;

		VkMemoryPropertyFlags temp_f = _flags;
		_flags = buffer._flags;
		buffer._flags = temp_f;
	}

	uint32_t Buffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
    {
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(Render_Core::get().getDevice().getPhysicalDevice(), &memProperties);

		for(uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
				return i;
		}

		Core::log::report(FATAL_ERROR, "Vulkan : failed to find suitable memory type");
		return 0; // Not necessary due to the FATAL_ERROR parameter for logs but that removes a warning
	}
}
