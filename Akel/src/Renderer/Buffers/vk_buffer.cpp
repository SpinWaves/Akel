// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 10/04/2022

#include "vk_buffer.h"

namespace Ak
{
	void Buffer::create(VkMemoryRequirements requirements, VkMemoryPropertyFlags flags const void* data)
	{
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

		if(vkAllocateMemory(device, &allocInfo, nullptr, &_mem_chunck.memory) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to allocate buffer memory");

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
