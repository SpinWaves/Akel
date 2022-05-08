// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/03/2022
// Updated : 08/05/2022

#include <Core/core.h>
#include "pages.h"
#include "chunk.h"

namespace Ak
{
	GPU_Page::Flag::Flag(unsigned int offset, unsigned int size)
	{
		this->offset = offset;
		this->size = size;
	}

	void GPU_Page::Flag::split(unsigned int start, unsigned int size)
	{
	    if(start == offset && this->size == size)
	        free = false;
	    else if (start > offset)
	    {
	        size_t startSpace = start - offset;
			size_t middleSpace = this->size - startSpace;
	        this->size = startSpace;

	        GPU_Page::Flag* middle = memAlloc<GPU_Page::Flag>(start, middleSpace);
	        middle->next = next;
	        next = middle;

	        middle->split(start, size);
	    }
	    else
	    {
	        free = false;
	        unsigned int endOffset = start + size;
	        unsigned int endSpace = (offset + this->size) - endOffset;
			this->size = size;

	        GPU_Page::Flag* end = memAlloc<GPU_Page::Flag>(endOffset, endSpace);
	        end->next = next;
	        next = end;
	    }
	}

	void GPU_Page::Flag::merge()
	{
	    if(free)
	    {
	       	GPU_Page::Flag* current = this->next;
	        while(current != nullptr && current->free)
	        {
	            size += current->size;
	            this->next = current->next;
	            memFree(current);
	        }
	    }
	}

	GPU_Page::GPU_Page(VkDevice device, size_t size, uint32_t typeIndex, std::unordered_map<VkDeviceMemory, GPU_Page*>& pageMap, VkAllocationCallbacks* callbacks)
	{
	    _size = size;
	    _mutex = create_unique_ptr_w<std::mutex>();
	    _device = device;
	    _callbacks = callbacks;
	    _typeIndex = typeIndex;

	    _head = memAlloc<GPU_Page::Flag>(0, size);

	    VkMemoryAllocateInfo info = {};
	    info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	    info.allocationSize = size;
	    info.memoryTypeIndex = typeIndex;

	    vkAllocateMemory(device, &info, callbacks, &_memory);

	    pageMap.insert({ _memory, this });
	}

	GPU_Page::GPU_Page(GPU_Page&& other)
	{
	    _head = std::move(other._head);
	    _size = other._size;
	    _mutex = std::move(other._mutex);
	    _device = other._device;
	    _memory = std::move(other._memory);
	    _callbacks = other._callbacks;

	    other._head = nullptr;
	    other._mutex = nullptr;
	    other._memory = VK_NULL_HANDLE;
	}

	GPU_Mem_Chunk GPU_Page::tryAlloc(VkMemoryRequirements requirements)
	{
	    if(requirements.size > _size)
	    	return {};
	    
	    std::lock_guard<std::mutex> watchdog(*_mutex);

	    GPU_Page::Flag* current = _head;

	    while(current)
	    {
	        if(current->free && current->size >= requirements.size)
	        {
	            size_t start = current->offset;
	            size_t available = current->size;

	            size_t unalign = start % requirements.alignment;
	            size_t align;

	            align = unalign ? 0 : align = requirements.alignment - unalign;

	            start += align;
	            available -= align;

	            if(available >= requirements.size)
	            {
	                current->split(start, requirements.size);
	                GPU_Mem_Chunk result;
	                result.memory = _memory;
	                result.offset = start;
	                result.size = requirements.size;
	                return result;
	            }
	        }

	        current = current->next;
	    }

	    return {};
	}

	void GPU_Page::free(GPU_Mem_Chunk allocation)
	{
	    std::lock_guard<std::mutex> watchdog(*_mutex);

	    GPU_Page::Flag* current = _head;

	    while(current)
	    {
	        if(current->free && current->offset == allocation.offset && current->size == allocation.size)
	        {
	            current->free = true;
	            break;
	        }
	    }

	    current = _head;

	    while(current)
	    {
	        current->merge();
	        current = current->next;
	    }
	}

	GPU_Page::~GPU_Page()
	{
	    vkFreeMemory(_device, _memory, _callbacks);

	    GPU_Page::Flag* current = _head;

	    while(current)
	    {
	        GPU_Page::Flag* next = current->next;
	    	memFree(current);
	        current = next;
	    }
	}
}
