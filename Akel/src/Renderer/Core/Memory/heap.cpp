// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/03/2022
// Updated : 01/04/2022

#include "heap.h"

namespace Ak
{
	GPU_Heap::GPU_Heap(uint32_t heapIndex, size_t pageSize, VkPhysicalDeviceMemoryProperties& props, VkDevice device, VkAllocationCallbacks* callbacks, std::unordered_map<VkDeviceMemory, Page*>& pageMap) : pageMap(pageMap)
    {
        this->heapIndex = heapIndex;
        this->pageSize = pageSize;
        mutex.reset(new std::mutex());
        this->callbacks = callbacks;
        this->device = device;

        for (size_t i = 0; i < props.memoryTypeCount; i++) {
            VkMemoryType& type = props.memoryTypes[i];

            if (type.heapIndex == heapIndex) {
                memoryTypes.emplace_back(MemoryType{ static_cast<uint32_t>(i), type.propertyFlags });
            }
        }
    }

    bool const GPU_HeapMatch(VkMemoryRequirements requirements, VkMemoryPropertyFlags flags, uint32_t* typeIndex) const {
        for (size_t i = 0; i < memoryTypes.size(); i++) {
            if ((requirements.memoryTypeBits & (1 << memoryTypes[i].typeIndex)) != 0 && (memoryTypes[i].flags & flags) == flags) {
                *typeIndex = static_cast<uint32_t>(i);
                return true;
            }
        }

        return false;
    }

    uint32_t const GPU_Heap::GetIndex() const {
        return heapIndex;
    }

    VkaAllocation GPU_Heap::Alloc(VkMemoryRequirements requirements, uint32_t typeIndex) {
        std::lock_guard<std::mutex> lock(*mutex);

        for (size_t i = 0; i < pages.size(); i++) {
            if (pages[i].Match(typeIndex)) {
                VkaAllocation result = pages[i].AttemptAlloc(requirements);
                if (result.memory != VK_NULL_HANDLE) {
                    return result;
                }
            }
        }

        size_t size = pageSize;
        if (requirements.size > size) size = requirements.size;
        pages.emplace_back(device, size, typeIndex, pageMap, callbacks);
        return pages[pages.size() - 1].AttemptAlloc(requirements);
    }
}
