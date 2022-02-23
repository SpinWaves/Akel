// This file is a part of Akel
// CREATED : 25/07/2021
// UPDATED : 03/02/2022

#include <Core/log.h>
#include <Maths/maths.h>

namespace Ak
{
    template <typename T = void, typename ... Args>
    T* JamAllocator::alloc(Args&& ... args)
    {
        if(_heap == nullptr)
        {
            Core::log::report(FATAL_ERROR, "Jam Allocator: you need to initialize the allocator before asking him to give you memory");
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
        BinarySearchTree<JamAllocator::flag*>* node = nullptr;
        if(_freeSpaces != nullptr)
        {
            if(_freeSpaces->has_data())
               node = _freeSpaces->find(&finder);
        }
        if(node != nullptr)
        {
            ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + (reinterpret_cast<uintptr_t>(node->getData()) - reinterpret_cast<uintptr_t>(_heap)));
            if(!_usedSpaces->has_data())
                _usedSpaces = node;
            else
                _usedSpaces->add(node); // Give node to Used Spaces Tree
            _freeSpaces->remove(node, false);
        }
        if(ptr == nullptr) // If we haven't found free flag
        {
            JamAllocator::flag* flag = reinterpret_cast<JamAllocator::flag*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // New flag
            flag->size = sizeType;
            _memUsed += sizeof(JamAllocator::flag);

            node = reinterpret_cast<BinarySearchTree<JamAllocator::flag*>*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // New Node
            init_node(node, flag);

            if(_usedSpaces == nullptr || !_usedSpaces->has_data())
                _usedSpaces = node;
            else
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

        JamAllocator::flag* finder = nullptr;
        BinarySearchTree<JamAllocator::flag*>* node = nullptr;
        size_t flag_size = sizeof(JamAllocator::flag);
        unsigned int better_flag = UINT_MAX;

        lockThreads(mutex);

        auto it = _usedSpaces->root_it();
        if(!it.has_data()) // used space tree is not supposed to be empty here
        {
            Core::log::report(ERROR, "Jam Allocator: an inconsistency was detected when a pointer was freed");
            return;
        }

        unsigned int cache = 0;

        for(; it.has_data(); it.next()) // flag finder
        {
            if((cache = reinterpret_cast<uintptr_t>(ptr) - (reinterpret_cast<uintptr_t>(it->getData()) + flag_size)) >= 0)
            {
                if(cache < better_flag)
                {
                    std::cout << it->getData() << std::endl;
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
            Core::log::report(ERROR, "JamAllocator : unable to find the flag of %p", ptr);
            unlockThreads(mutex);
            return;
        }
        
        _usedSpaces->remove(node, false);
        
        if(_freeSpaces == nullptr || !_freeSpaces->has_data())
            _freeSpaces = node;
        else
            _freeSpaces->add(node);
        
        unlockThreads(mutex);
        ptr = nullptr;
    }
}
