// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/07/2021
// Updated : 18/03/2023

#include <Core/core.h>

namespace Ak
{
    void JamAllocator::init(size_t Size)
    {
        if(_heap != nullptr)
            return;

        std::unique_lock<std::mutex> watchdog(_general_mutex, std::try_to_lock);

        _heap = std::malloc(Size);

        if(!_heap)
            Core::log::report(FATAL_ERROR, "JamAllocator : unable to allocate memory space for an allocator");

        _heapSize = Size;
        _heapEnd = (void*)(reinterpret_cast<uintptr_t>(_heap) + _heapSize);

        _allocator_number = MemoryManager::accessToControlUnit()->jamStack.size();
        std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
        getMainAppProjectFile().setIntValue(key, Size);
        MemoryManager::accessToControlUnit()->jamStack.push_back(weak_from_this());
    }

    void JamAllocator::increase_size(size_t Size)
    {
        if(Size < _heapSize)
        {
            Core::log::report(WARNING, "JamAllocator : Akel's JamAllocators cannot reduce their size");
            return;
        }

        std::unique_lock<std::mutex> watchdog(_general_mutex, std::try_to_lock);

        if(Size > _heapSize)
        {
            _resises.push_back(std::make_pair(std::malloc(Size - _heapSize), Size - _heapSize));

            _heapSize = Size;
            std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
            getMainAppProjectFile().setIntValue(key, Size);
        }
    }

    void JamAllocator::destroy()
    {
        if(_heap == nullptr)
            return;

        std::unique_lock<std::mutex> watchdog(_general_mutex, std::try_to_lock);

        std::free(_heap);
        _heap = nullptr;
        
        std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
        getMainAppProjectFile().setIntValue(key, _memUsed);
    }

	void* JamAllocator::internal_allocation(size_t size)
	{
        if(_heap == nullptr)
        {
			Core::log::report(FATAL_ERROR, "Jam Allocator: you need to initialize the allocator before asking him to give you memory");
            return nullptr;
        }
        if(!canHold(size))
        {
            //if(_autoResize)
            //    increase_size(_heapSize * (4/3));
            //else
            {
				Core::log::report(FATAL_ERROR, "Jam Allocator: the requested allocation is too large for the allocator (%d > %d), free up memory or increase the size of the allocator", size, _heapSize - _memUsed);
                return nullptr;
            }
        }

        void* ptr = nullptr;

        std::unique_lock<std::mutex> watchdog(_alloc_mutex, std::try_to_lock);

        if(!_freeSpaces.empty())
        {
			auto it = _freeSpaces.lower_bound(size);
			if(it != _freeSpaces.end())
			{
				JamAllocator::flag flag = it->first;
				ptr = it->second;
				_freeSpaces.erase(it);
				if(ptr != nullptr)
					_usedSpaces.emplace(std::make_pair(flag, ptr));
			}
        }

        if(ptr == nullptr)
        {
            JamAllocator::flag flag = size;
            ptr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed);
			_usedSpaces.emplace(std::make_pair(flag, ptr));
            _memUsed += size;
        }

        watchdog.unlock();

		if(ptr == nullptr)
			Error("JamAllocator : unable to allocate %d bytes", size);

        return ptr;
	}

	void JamAllocator::internal_free(void* ptr)
	{
        std::unique_lock<std::mutex> watchdog(_free_mutex, std::try_to_lock);
        uint32_t cache;
        uint32_t better_flag = -1;
		JamAllocator::flag flag;
		auto iterator = _usedSpaces.end();

        for(auto it = _usedSpaces.begin(); it != _usedSpaces.end(); ++it)
        {
            if((cache = reinterpret_cast<uintptr_t>(ptr) - reinterpret_cast<uintptr_t>(it->second)) >= 0)
            {
                if(cache < better_flag)
                {
                    flag = it->first;
					iterator = it;
                    better_flag = cache;
                }
                if(better_flag == 0) // we found the exact flag
                    break;
            }
        }

        if(iterator == _usedSpaces.end())
        {
            Error("JamAllocator : unable to find the flag of %p", ptr);
            watchdog.unlock();
            return;
        }
        
        _usedSpaces.erase(iterator);
		_freeSpaces.emplace(std::make_pair(flag, ptr));

        watchdog.unlock();
	}

    JamAllocator::~JamAllocator()
    {
        destroy();
    }
}
