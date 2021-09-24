// This file is a part of Akel
// CREATED : 24/09/2021
// UPDATED : 24/09/2021

#include <Renderer/Memory/chunk.h>
#include <Core/core.h>

namespace Ak
{
    bool Buffer::operator == (Buffer const& buffer)
    {
        if(memory == buffer.memory && offset == buffer.offset && size == buffer.size && free == buffer.free && ptr == buffer.ptr)
            return true;
        return false;
    }

    Chunk::Chunk(VkDeviceSize size, int memoryTypeIndex) : LowestInheritance()
    {
        _size = size;
        _memoryTypeIndex = memoryTypeIndex;

        VkMemoryAllocateInfo allocateInfo{};
        allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocateInfo.allocationSize = size;
        allocateInfo.memoryTypeIndex = memoryTypeIndex;

        Buffer buffer;
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
        for(auto it = _buffers.begin(); it != _buffers.end(); it++)
        {
            if(*it == buffer)
                return true;
        }
        return false;
    }
#pragma GCC diagnostic pop

    bool Chunk::alloc(VkDeviceSize size, Buffer& buffer, VkDeviceSize alignment)
    {
        if(size > _size)
            return false;

        for(Buffer& bufferAllocated : _buffers)
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
                        buffer = bufferAllocated;
                        return true;
                    }

                    Buffer nextBuffer;
                    nextBuffer.free = true;
                    nextBuffer.offset = bufferAllocated.offset + size;
                    nextBuffer.memory = _memory;
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

    void Chunk::free(const Buffer& buffer)
    {
        auto bufferIt(std::find(_buffers.begin(), _buffers.end(), buffer));
        if(bufferIt == _buffers.end())
            Core::log::report(FATAL_ERROR, "Vulkan : Allocator_GPU : Chunck : free(const Buffer&) : unable to find the buffer in the stack, it cannot be freed");
        bufferIt->free = true;
    }
}
