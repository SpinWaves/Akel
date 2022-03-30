// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/07/2021
// Updated : 30/03/2022

#include <Core/core.h>

namespace Ak
{
    void JamAllocator::init(size_t Size) : _mutex()
    {
        if(_heap != nullptr)
            return;

        _mutex.lockThreads();

        _heap = std::malloc(Size);

        if(!_heap)
            Core::log::report(FATAL_ERROR, "JamAllocator : unable to allocate memory space for an allocator");

        _heapSize = Size;
        _heapEnd = (void*)(reinterpret_cast<uintptr_t>(_heap) + _heapSize);

        _allocator_number = MemoryManager::accessToControlUnit()->jamStack.size();
        std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(key, Size);
        MemoryManager::accessToControlUnit()->jamStack.push_back(weak_from_this());

        _mutex.unlockThreads();
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

        _mutex.lockThreads();

        if(Size > _heapSize)
        {
            _resises.push_back(std::make_pair(std::malloc(Size - _heapSize), Size - _heapSize));

            _heapSize = Size;
            std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
            Core::ProjectFile::setIntValue(key, Size);
        }

        _mutex.unlockThreads();
    }

    void JamAllocator::destroy()
    {
        if(_heap == nullptr)
            return;

        _mutex.lockThreads();

        _freeSpaces = nullptr;
        _usedSpaces = nullptr;

        std::free(_heap);
        _heap = nullptr;
        
        std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(key, _memUsed);

        _mutex.unlockThreads();
    }

    JamAllocator::~JamAllocator()
    {
        destroy();
    }
}
