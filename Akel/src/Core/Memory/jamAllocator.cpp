// This file is a part of Akel
<<<<<<< HEAD
// Authors : @kbz_8
// Created : 20/07/2021
// Updated : 24/02/2022
=======
// CREATED : 20/07/2021
<<<<<<< HEAD
// UPDATED : 08/01/2022
>>>>>>> working on path for jamallocator
=======
// UPDATED : 15/01/2022
>>>>>>> almost finishing JamAllocator 2.0.1 patch

#include <Core/core.h>

namespace Ak
{
    void JamAllocator::init(size_t Size)
    {
        if(_heap != nullptr)
            return;

        #if defined(AK_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
              InitializeCriticalSection(&mutex);
        #endif

        lockThreads(mutex);

        _heap = std::malloc(Size);

        if(!_heap)
            Core::log::report(FATAL_ERROR, "JamAllocator : unable to allocate memory space for an allocator");

        _heapSize = Size;
        _heapEnd = (void*)(reinterpret_cast<uintptr_t>(_heap) + _heapSize);

        _allocator_number = MemoryManager::accessToControlUnit()->jamStack.size();
        std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(key, Size);
        MemoryManager::accessToControlUnit()->jamStack.push_back(weak_from_this());

        unlockThreads(mutex);
    }

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    void JamAllocator::init_node(BinarySearchTree<JamAllocator::flag*>* node, JamAllocator::flag* flag)
    {
        new ((void*)node) BinarySearchTree<JamAllocator::flag*>(std::move(flag)); // Give flag to node (node is not init, just allocated so we call his constructor)
        node->set_greater_operation([](JamAllocator::flag* new_d, JamAllocator::flag* curr_d) { return new_d->size  > curr_d->size; } );
        node->set_equal_operation(  [](JamAllocator::flag* new_d, JamAllocator::flag* curr_d) { return new_d->size == curr_d->size; } );
        node->set_less_operation(   [](JamAllocator::flag* new_d, JamAllocator::flag* curr_d) { return new_d->size  < curr_d->size; } );
        _memUsed += sizeof(BinarySearchTree<JamAllocator::flag*>);
=======
    void JamAllocator::init_node(BinarySearchTree<JamAllocator::flag&>* node, JamAllocator::flag& flag)
    {
        new ((void*)node) BinarySearchTree<JamAllocator::flag&>(flag); // Give flag to node (node is not init, just allocated so we call his constructor)
>>>>>>> working on path for jamallocator
=======
    void JamAllocator::init_node(BinarySearchTree<const JamAllocator::flag&>* node, const JamAllocator::flag& flag)
    {
        new ((void*)node) BinarySearchTree<const JamAllocator::flag&>(flag); // Give flag to node (node is not init, just allocated so we call his constructor)
>>>>>>> working on a patch for jamallocator
=======
    void JamAllocator::init_node(BinarySearchTree<JamAllocator::flag*>* node, JamAllocator::flag* flag)
    {
        new ((void*)node) BinarySearchTree<JamAllocator::flag*>(std::move(flag)); // Give flag to node (node is not init, just allocated so we call his constructor)
        node->set_greater_operation([](JamAllocator::flag* new_d, JamAllocator::flag* curr_d) { return new_d->size  > curr_d->size; } );
        node->set_equal_operation(  [](JamAllocator::flag* new_d, JamAllocator::flag* curr_d) { return new_d->size == curr_d->size; } );
        node->set_less_operation(   [](JamAllocator::flag* new_d, JamAllocator::flag* curr_d) { return new_d->size  < curr_d->size; } );
        _memUsed += sizeof(BinarySearchTree<JamAllocator::flag*>);
>>>>>>> almost finishing JamAllocator 2.0.1 patch
    }

    void JamAllocator::increase_size(size_t Size)
    {
        if(Size < _heapSize)
        {
            Core::log::report(WARNING, "JamAllocator : Akel's JamAllocators cannot reduce their size");
            return;
        }

        lockThreads(mutex);

        if(Size > _heapSize)
        {
            _resises.push_back(std::make_pair(std::malloc(Size - _heapSize), Size - _heapSize));

            _heapSize = Size;
            std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
            Core::ProjectFile::setIntValue(key, Size);
        }

        unlockThreads(mutex);
    }

    void JamAllocator::destroy()
    {
        if(_heap == nullptr)
            return;

        lockThreads(mutex);

        _freeSpaces = nullptr;
        _usedSpaces = nullptr;

        std::free(_heap);
        _heap = nullptr;
        
        std::string key = "jamAllocator_size_" + std::to_string(_allocator_number);
        Core::ProjectFile::setIntValue(key, _memUsed);

        unlockThreads(mutex);
    }

    JamAllocator::~JamAllocator()
    {
        destroy();

        #if defined(AK_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            DeleteCriticalSection(&mutex);
        #endif
    }
}
