// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/03/2022
// Updated : 28/11/2022

#include "heap.h"

namespace Ak
{
	GPU_Heap::GPU_Heap(uint32_t heapIndex, size_t pageSize, VkPhysicalDeviceMemoryProperties& props, VkDevice device, VkAllocationCallbacks* callbacks, std::unordered_map<VkDeviceMemory, GPU_Page*>& pageMap) : _pageMap(pageMap)
    {
        _heapIndex = heapIndex;
        _pageSize = pageSize;
        _callbacks = callbacks;
        _device = device;

        for(uint32_t i = 0; i < props.memoryTypeCount; i++)
        {
            VkMemoryType& type = props.memoryTypes[i];

            if(type.heapIndex == _heapIndex)
                _memoryTypes.emplace_back(MemoryType{ i, type.propertyFlags });
		}
    }

	bool const GPU_Heap::match(VkMemoryRequirements requirements, VkMemoryPropertyFlags flags, uint32_t* typeIndex) const
    {
        for(uint32_t i = 0; i < _memoryTypes.size(); i++)
        {
            if((requirements.memoryTypeBits & (1 << _memoryTypes[i].typeIndex)) && (_memoryTypes[i].flags & flags) == flags)
            {
                *typeIndex = i;
                return true;
            }
        }

        return false;
    }

    GPU_Mem_Chunk GPU_Heap::allocChunk(VkMemoryRequirements requirements, uint32_t typeIndex)
    {
        for(size_t i = 0; i < _pages.size(); i++)
        {
            if(_pages[i].match(typeIndex))
            {
                GPU_Mem_Chunk result = _pages[i].tryAlloc(requirements);
                if(result.memory != VK_NULL_HANDLE)
                    return result;
            }
        }

        size_t size = _pageSize;
        if(requirements.size > size)
            size = requirements.size;
        _pages.emplace_back(_device, size, typeIndex, _pageMap, _callbacks);
        return _pages.back().tryAlloc(requirements);
    }
}
