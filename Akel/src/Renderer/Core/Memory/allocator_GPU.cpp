// This file is a part of Akel
// Authors : @kbz_8
// Created : 24/09/2021
// Updated : 12/08/2022

#include "allocator_GPU.h"
#include "pages.h"
#include "chunk.h"
#include <Core/core.h>

namespace Ak
{
    void Allocator_GPU::init(VkPhysicalDevice physicalDevice, VkDevice device, VkAllocationCallbacks* callbacks, size_t pageSize)
    {
        _physicalDevice = physicalDevice;
        _device = device;
        _callbacks = callbacks;

        VkPhysicalDeviceMemoryProperties props;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &props);

        for(uint32_t i = 0; i < props.memoryHeapCount; i++)
            _heaps.emplace_back(i, pageSize, props, device, callbacks, _pageMap);
    }

    GPU_Mem_Chunk Allocator_GPU::allocChunk(VkMemoryRequirements requirements, VkMemoryPropertyFlags flags)
    {
        std::lock_guard<std::mutex> watchdog(_mutex);
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

        Core::log::report(ERROR, "GPU Allocator : cannot allocate a chunk of GPU memory, not enought free space available");

        return {};
    }

    void Allocator_GPU::freeChunk(GPU_Mem_Chunk allocation)
    {
        std::lock_guard<std::mutex> watchdog(_mutex);
        if(_pageMap.count(allocation.memory) == 0)
		{
			Core::log::report(ERROR, "GPU Allocator : cannot find on which heap the chunk has been allocated [wtf this should not happen]");
			return;
		}
        GPU_Page* page = _pageMap[allocation.memory];
        page->free(allocation);
    }
}
