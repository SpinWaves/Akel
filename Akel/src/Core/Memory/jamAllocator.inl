// This file is a part of Akel
// CREATED : 25/07/2021
// UPDATED : 03/01/2022

#include <Core/Memory/jamAllocator.h>
#include <Core/log.h>

namespace Ak
{
    template <typename T = void, typename ... Args>
    T* JamAllocator::alloc(Args&& ... args)
    {
        if(_heap == nullptr)
        {
            Core::log::report(FATAL_ERROR, "Jam Allocator: you need to initialize the allocator before aking him to give you memory");
            return nullptr;
        }
        size_t sizeType = sizeof(T);
        if(!canHold(sizeType))
        {
            if(_autoResize)
                increase_size(_heapSize * (4/3));
            else
            {
                Core::log::report(FATAL_ERROR, "Jam Allocator: the requested allocation is too large for the allocator, free up memory or increase the size of the allocator");
                return nullptr;
            }
        }

        T* ptr = nullptr;

        lockThreads(mutex);

        JamAllocator::flag finder;
        finder.size = sizeType;
        finder.offset = 0;
        BinarySearchTree<JamAllocator::flag&>* node = _freeSpaces->find(finder);
        if(node != nullptr)
        {
            ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + node->getData().offset + sizeof(JamAllocator::flag));
            _usedSpaces->add(node->getData());
            _freeSpaces->remove(finder);
        }
        if(ptr == nullptr) // If we haven't found free flag
        {
            node = reinterpret_cast<BinarySearchTree<JamAllocator::flag&>>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // New Node
            _memUsed += sizeof(BinarySearchTree<JamAllocator::flag&>);

            JamAllocator::flag* flag_ptr = static_cast<flag*>((void*)(reinterpret_cast<uintptr_t>(_heap) + _memUsed)); // New Flag
            flag_ptr->size = sizeType;
            flag_ptr->offset = _memUsed;
            new ((void*)node) BinarySearchTree<JamAllocator::flag&>(*flag_ptr); // Give flag to node (node is not init, just allocated so we call his constructor)
            _memUsed += sizeof(JamAllocator::flag);

            _usedSpaces->add(node); // Give node to Used Spaces Tree
            ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // Allocate Pointer
            _memUsed += sizeType;
        }

        unlockThreads(mutex);

        if(std::is_class<T>::value)
            new ((void*)ptr) T(std::forward<Args>(args)...);

    	return ptr;
    }

    template <typename T = void>
    void JamAllocator::free(T* ptr)
    {
        if(ptr == nullptr)
        {
            Core::log::report(WARNING, "Jam Allocator: you cannot free a nullptr");
            return;
        }
        if(_heap == nullptr)
        {
            Core::log::report(WARNING, "Jam Allocator: trying to free a pointer with an uninitialised allocator");
            return;
        }
        if(!contains((void*)ptr))
        {
            Core::log::report(WARNING, "Jam Allocator: a pointer allocated by another allocator is trying to be freed");
            return;
        }
        if(std::is_class<T>::value)
            ptr->~T();

        JamAllocator::flag flag_ref;
        JamAllocator::flag* finder = nullptr;

        lockThreads(mutex);

        auto it = _usedSpaces->root_it();

        for(; it.hasNext(); it.next()) // flag finder
        {
            if(ptr >= (void*)(reinterpret_cast<uintptr_t>(_heap) + (*it).getData().offset + sizeof(JamAllocator::flag)))
                finder = &(*it).getData();
        }

        if(finder != nullptr)
        {
            flag_ref.size = (*it).getData().size;
            flag_ref.offset = (*it).getData().offset;
            _usedSpaces->remove(it.get_node());
        }
        else
        {
            flag_ref.size = 0;
            flag_ref.offset = 0;
        }
        
        if(flag_ref.size == 0 && flag_ref.offset == 0)
        {
            Core::log::report(ERROR, "JamAllocator : unable to find the flag of %p", ptr);
            unlockThreads(mutex);
            return;
        }

        _freeSpaces->add(flag_ref);
        unlockThreads(mutex);
        ptr = nullptr;
    }
}
