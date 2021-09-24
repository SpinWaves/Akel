// This file is a part of Akel
// CREATED : 24/09/2021
// UPDATED : 24/09/2021

#ifndef __AK_VULKAN_GPU_MEMORY_CHUNK__
#define __AK_VULKAN_GPU_MEMORY_CHUNK__

#include <Renderer/Memory/allocator_GPU.h>
#include <Core/core.h>

namespace Ak::Allocator_GPU
{
    Chunk::Chunk(VkDeviceSize size, int memoryTypeIndex) : lowestInheritance()
    {
        _device = device;
        _size = size;
        _memoryTypeIndex = memoryTypeIndex;

        VkMemoryAllocateInfo allocateInfo(size, memoryTypeIndex);

        Buffer block;
        buffer.free = true;
        buffer.offset = 0;
        buffer.size = size;
        if(vkAllocateMemory(device, &allocateInfo, nullptr, &buffer.memory) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to allocate buffer memory");
        _memory = buffer.memory;

        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        if((memProperties.memoryTypes[memoryTypeIndex].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
            vkMapMemory(device, _memory, 0, VK_WHOLE_SIZE, 0, &_ptr);

        _buffers.emplace_back(buffer);
    }

#pragma GCC diagnostic push
// to avoid "warning: always_inline function might not be inlinable [-Wattributes]"
#pragma GCC diagnostic ignored "-Wattributes"
    forceinline bool Chunk::isIn(const Buffer& buffer)
    {
        auto bufferIt(std::find(_buffers.begin(), _buffers.end(), buffer));
        return bufferIt == _buffers.end();
    }
#pragma GCC diagnostic pop

    bool Chunck::alloc(VkDeviceSize size, const Buffer& buffer, VkDeviceSize alignment)
    {
        if(size > _size)
            return false;

        for(auto bufferAllocated : _buffers)
        {
            if(bufferAllocated.free)
            {
                uint32_t newSize = bufferAllocated.size;

                if(bufferAllocated.offset % alignment != 0)
                    newSize -= alignment - bufferAllocated.offset % alignment;

                if(newSize >= size)
                {

                    bufferAllocated.size = newSize;
                    if(bufferAllocated.offset % alignment != 0)
                        bufferAllocated.offset += alignment - bufferAllocated.offset % alignment;

                    if(_ptr != nullptr)
                        bufferAllocated.ptr = (char*)_ptr + bufferAllocated.offset;

                    if(bufferAllocated.size == size)
                    {
                        bufferAllocated.free = false;
                        block = bufferAllocated;
                        return true;
                    }

                    Buffer nextBuffer;
                    nextBuffer.free = true;
                    nextBuffer.offset = bufferAllocated.offset + size;
                    nextBuffer.memory = mMemory;
                    nextBuffer.size = bufferAllocated.size - size;
                    _buffers.emplace_back(nextBuffer);

                    bufferAllocated.size = size;
                    bufferAllocated.free = false;

                    buffer = bufferAllocated;
                    return true;
                }
            }
        }
        return false;
    }

    void Chunck::free(const Buffer& buffer)
    {
        auto bufferIt(std::find(_buffers.begin(), _buffers.end(), buffer));
        if(bufferIt == _buffers.end())
            Core::log::report(FATAL_ERROR, "Vulkan : Allocator_GPU : Chunck : free(const Buffer&) : unable to find the buffer in the stack, it cannot be freed");
        bufferIt->free = true;
    }
}

#endif // __AK_VULKAN_GPU_MEMORY_CHUNK__
