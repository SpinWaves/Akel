// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2022
// Updated : 19/11/2023

#include <Renderer/Buffers/vk_buffer.h>
#include <Utils/assert.h>
#include <Renderer/Command/vk_cmd_pool.h>

namespace Ak
{
	void Buffer::create(Buffer::kind type, VkDeviceSize size, VkBufferUsageFlags usage, const void* data)
	{
		_usage = usage;
		if(type == Buffer::kind::constant)
		{
			if(data == nullptr)
			{
				Core::log::report(WARNING, "Vulkan : trying to create constant buffer without data (constant buffers cannot be modified after creation)");
				return;
			}
			_usage |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		}

		VmaAllocationCreateInfo alloc_info{};
		alloc_info.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;
		alloc_info.usage = VMA_MEMORY_USAGE_AUTO;

		createBuffer(_usage, alloc_info, size);

		if(data != nullptr)
		{
			void* mapped = nullptr;
			mapMem(&mapped);
				std::memcpy(mapped, data, size);
			unmapMem();
			if(type == Buffer::kind::constant)
				pushToGPU();
		}
	}

	void Buffer::destroy() noexcept
	{
		Ak_assert(_buffer != VK_NULL_HANDLE, "trying to destroy an uninit video buffer");
		if(_is_mapped)
			unmapMem();
		Render_Core::get().getAllocator().destroyBuffer(_allocation, _buffer);
		_buffer = VK_NULL_HANDLE;
	}

	void Buffer::createBuffer(VkBufferUsageFlags usage, VmaAllocationCreateInfo info, VkDeviceSize size)
	{
		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		_allocation = Render_Core::get().getAllocator().createBuffer(&bufferInfo, &info, _buffer, nullptr);
		Ak_assert(_buffer != VK_NULL_HANDLE, "Vulkan : something went wrong in the creation of a buffer");
		_size = size;
	}

	void Buffer::pushToGPU() noexcept
	{
		VmaAllocationCreateInfo alloc_info{};
		alloc_info.usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;

		Buffer newBuffer;
		newBuffer._usage = (_usage & 0xFFFFFFFC) | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
		newBuffer.createBuffer(newBuffer._usage, alloc_info, _size);

		CmdPool cmdpool;
		cmdpool.init();
		CmdBuffer cmdBuffer;
		cmdBuffer.init(&cmdpool);

		cmdBuffer.beginRecord(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

		VkBufferCopy copyRegion{};
		copyRegion.size = _size;
		vkCmdCopyBuffer(cmdBuffer.get(), _buffer, newBuffer._buffer, 1, &copyRegion);

		cmdBuffer.endRecord();
		cmdBuffer.submitIdle();

		cmdBuffer.destroy();
		cmdpool.destroy();

		this->swap(newBuffer);

		newBuffer.destroy();
		Core::log::report(DEBUGLOG, "Vulkan : pushed buffer to GPU");
	}

	void Buffer::swap(Buffer& buffer)
	{
		VkBuffer temp_b = _buffer;
		_buffer = buffer._buffer;
		buffer._buffer = temp_b;

		VmaAllocation temp_a = buffer._allocation;
		buffer._allocation = _allocation;
		_allocation = temp_a;

		VkDeviceSize temp_size = buffer._size;
		buffer._size = _size;
		_size = temp_size;

		VkDeviceSize temp_offset = buffer._offset;
		buffer._offset = _offset;
		_offset = temp_offset;

		VkBufferUsageFlags temp_u = _usage;
		_usage = buffer._usage;
		buffer._usage = temp_u;
	}

	void Buffer::flush(VkDeviceSize size, VkDeviceSize offset)
	{
		Render_Core::get().getAllocator().flush(_allocation, size, offset);
	}
}
