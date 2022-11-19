// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/07/2021
// Updated : 19/11/2022

#include <Core/core.h>

namespace Ak
{
    void JamAllocator::init(size_t Size)
    {
        if(_heap != nullptr)
            return;

        std::unique_lock<std::mutex> watchdog(_mutex, std::try_to_lock);

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

    void JamAllocator::init_node(BinarySearchTree<JamAllocator::flag*>* node, JamAllocator::flag* flag)
    {
        new ((void*)node) BinarySearchTree<JamAllocator::flag*>(std::move(flag)); // Give flag to node (node is not init, just allocated so we call his constructor)
        node->set_greater_operation([](JamAllocator::flag* new_d, JamAllocator::flag* curr_d) { return new_d->size  > curr_d->size; } );
        node->set_equal_operation(  [](JamAllocator::flag* new_d, JamAllocator::flag* curr_d) { return new_d->size == curr_d->size; } );
        node->set_less_operation(   [](JamAllocator::flag* new_d, JamAllocator::flag* curr_d) { return new_d->size  < curr_d->size; } );
        _memUsed += sizeof(BinarySearchTree<JamAllocator::flag*>);
    }

    void JamAllocator::increase_size(size_t Size)
    {
        if(Size < _heapSize)
        {
            Core::log::report(WARNING, "JamAllocator : Akel's JamAllocators cannot reduce their size");
            return;
        }

        std::unique_lock<std::mutex> watchdog(_mutex, std::try_to_lock);

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

        std::unique_lock<std::mutex> watchdog(_mutex, std::try_to_lock);

        _freeSpaces = nullptr;
        _usedSpaces = nullptr;

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
        BinarySearchTree<JamAllocator::flag*>* node = nullptr;

        std::unique_lock<std::mutex> watchdog(_mutex, std::try_to_lock);

        if(_freeSpaces != nullptr && _freeSpaces->has_data())
        {
			JamAllocator::flag finder;
			finder.size = size;
		   node = _freeSpaces->find(&finder);
        }
        if(node != nullptr)
        {
            ptr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(_heap) + (reinterpret_cast<uintptr_t>(node->getData()) - reinterpret_cast<uintptr_t>(_heap)));
            if(!_usedSpaces->has_data())
                _usedSpaces = node;
            else
                _usedSpaces->add(node); // Give node to Used Spaces Tree
            _freeSpaces->remove(node, false);
        }
        if(ptr == nullptr) // If we haven't found free flag
        {
            JamAllocator::flag* flag = reinterpret_cast<JamAllocator::flag*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // New flag
            flag->size = size;
            _memUsed += sizeof(JamAllocator::flag);
            _memUsed += sizeof(_freeSpaces);

            node = reinterpret_cast<BinarySearchTree<JamAllocator::flag*>*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // New Node
            init_node(node, flag);

            if(_usedSpaces == nullptr || !_usedSpaces->has_data())
                _usedSpaces = node;
            else
                _usedSpaces->add(node); // Give node to Used Spaces Tree
            ptr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // Allocate Pointer
            _memUsed += size;
        }

        watchdog.unlock();

        return ptr;
	}

	void JamAllocator::internal_free(void* ptr)
	{
        JamAllocator::flag* finder = nullptr;
        BinarySearchTree<JamAllocator::flag*>* node = nullptr;
        unsigned int better_flag = -1;

        std::unique_lock<std::mutex> watchdog(_mutex, std::try_to_lock);

        auto it = _usedSpaces->root_it();
        if(!it.has_data())
        {
            watchdog.unlock();
            return;
        }

        unsigned int cache = 0;

        for(; it.has_data(); it.next()) // flag finder
        {
            if((cache = reinterpret_cast<uintptr_t>(ptr) - (reinterpret_cast<uintptr_t>(it->getData()) + sizeof(JamAllocator::flag))) >= 0)
            {
                if(cache < better_flag)
                {
                    finder = it->getData();
                    node = it.get_node();
                    better_flag = cache;
                }
                if(better_flag == 0) // we found the exact flag
                    break;
            }
        }

        if(finder == nullptr)
        {
            Error("JamAllocator : unable to find the flag of %p", ptr);
            watchdog.unlock();
            return;
        }
        
        _usedSpaces->remove(node, false);
        
        if(_freeSpaces == nullptr || !_freeSpaces->has_data())
            _freeSpaces = node;
        else
            _freeSpaces->add(node);

        watchdog.unlock();
	}

    JamAllocator::~JamAllocator()
    {
        destroy();
    }
}
