// This file is a part of Akel
// Authors : @kbz_8
// Created : 24/09/2021
// Updated : 01/04/2022

#include "allocator_GPU.h"
#include "pages.h"
#include "chunck.h"
#include <Core/core.h>

namespace Ak
{
    Allocator_GPU::Allocator_GPU(VkPhysicalDevice physicalDevice, VkDevice device, VkAllocationCallbacks* callbacks, size_t pageSize)
    {
        _physicalDevice = physicalDevice;
        _device = device;
        _callbacks = callbacks;

        VkPhysicalDeviceMemoryProperties props;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &props);

        for(size_t i = 0; i < props.memoryHeapCount; i++)
            _heaps.emplace_back(static_cast<uint32_t>(i), pageSize, props, device, callbacks, _pageMap);
    }

    GPU_Mem_Chunk Allocator_GPU::allocChunck(VkMemoryRequirements requirements, VkMemoryPropertyFlags flags)
    {
        for(size_t i = 0; i < _heaps.size(); i++)
        {
            uint32_t typeIndex = 0;
            if(_heaps[i].match(requirements, flags, &typeIndex))
            {
                GPU_Mem_Chunk result = _heaps[i].allocChunk(requirements, typeIndex);
                if(result.memory != VK_NULL_HANDLE)
                    return result;
            }
        }

        return {};
    }

    void Allocator_GPU::freeChunk(GPU_Mem_Chunk allocation)
    {
        if(pageMap.count(allocation.memory) == 0)
            return;
        GPU_Page* page = _pageMap[allocation.memory];
        page->free(allocation);
    }
}
