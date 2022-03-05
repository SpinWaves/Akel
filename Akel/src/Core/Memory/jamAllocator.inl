// This file is a part of Akel
<<<<<<< HEAD
// Authors : @kbz_8
// Created : 25/07/2021
// Updated : 03/02/2022
=======
// CREATED : 25/07/2021
// UPDATED : 15/01/2022
>>>>>>> almost finishing JamAllocator 2.0.1 patch

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
<<<<<<< HEAD
        BinarySearchTree<JamAllocator::flag*>* node = nullptr;
=======
        finder.offset = 0;
<<<<<<< HEAD
        BinarySearchTree<const JamAllocator::flag&>* node = nullptr;
>>>>>>> working on a patch for jamallocator
=======
        BinarySearchTree<JamAllocator::flag*>* node = nullptr;
>>>>>>> almost finishing JamAllocator 2.0.1 patch
        if(_freeSpaces != nullptr)
        {
            if(_freeSpaces->has_data())
               node = _freeSpaces->find(&finder);
        }
        if(node != nullptr)
        {
<<<<<<< HEAD
            ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + (reinterpret_cast<uintptr_t>(node->getData()) - reinterpret_cast<uintptr_t>(_heap)));
=======
            ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + node->getData()->offset);
>>>>>>> almost finishing JamAllocator 2.0.1 patch
            if(!_usedSpaces->has_data())
                _usedSpaces = node;
            else
                _usedSpaces->add(node); // Give node to Used Spaces Tree
            _freeSpaces->remove(node, false);
        }
        if(ptr == nullptr) // If we haven't found free flag
        {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
            JamAllocator::flag* flag = reinterpret_cast<JamAllocator::flag*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // New flag
            flag->size = sizeType;
            _memUsed += sizeof(JamAllocator::flag);
=======
            node = reinterpret_cast<BinarySearchTree<JamAllocator::flag&>*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // New Node
=======
            node = reinterpret_cast<BinarySearchTree<const JamAllocator::flag&>*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // New Node
>>>>>>> working on a patch for jamallocator
            _memUsed += sizeof(_freeSpaces);
=======
            JamAllocator::flag* flag = reinterpret_cast<JamAllocator::flag*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // New flag
            flag->size = sizeType;
            _memUsed += sizeof(JamAllocator::flag);
>>>>>>> almost finishing JamAllocator 2.0.1 patch

            node = reinterpret_cast<BinarySearchTree<JamAllocator::flag*>*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // New Node
            init_node(node, flag);
<<<<<<< HEAD
>>>>>>> working on path for jamallocator

            node = reinterpret_cast<BinarySearchTree<JamAllocator::flag*>*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // New Node
            init_node(node, flag);
=======
            flag->offset = _memUsed; // Set offset here to include node size
>>>>>>> almost finishing JamAllocator 2.0.1 patch

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

<<<<<<< HEAD
<<<<<<< HEAD
        JamAllocator::flag* finder = nullptr;
        BinarySearchTree<JamAllocator::flag*>* node = nullptr;
        size_t flag_size = sizeof(JamAllocator::flag);
        unsigned int better_flag = UINT_MAX;
=======
        JamAllocator::flag flag_ref;
        const JamAllocator::flag* finder;
>>>>>>> working on a patch for jamallocator
=======
        JamAllocator::flag* finder = nullptr;
>>>>>>> almost finishing JamAllocator 2.0.1 patch

        lockThreads(mutex);

        auto it = _usedSpaces->root_it();
        if(!it.has_data()) // used space tree is not supposed to be empty here
        {
<<<<<<< HEAD
            Core::log::report(ERROR, "Jam Allocator: an inconsistency was detected when a pointer was freed");
            return;
        }

<<<<<<< HEAD
        unsigned int cache = 0;

        for(; it.has_data(); it.next()) // flag finder
=======
        if(finder)
=======
            if(ptr == (void*)(reinterpret_cast<uintptr_t>(_heap) + it->getData()->offset))
                finder = it->getData();
        }

        bool oui = (void*)ptr == (void*)(finder + sizeof(JamAllocator::flag));
        std::cout << ptr << "   " << finder + sizeof(JamAllocator::flag) << "    match : " << oui << std::endl;

        if(finder != nullptr)
>>>>>>> almost finishing JamAllocator 2.0.1 patch
        {
            debugPrint(it->getData());
            _usedSpaces->remove(it.get_node(), false);
        }
        else
>>>>>>> working on a patch for jamallocator
        {
<<<<<<< HEAD
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
=======
>>>>>>> almost finishing JamAllocator 2.0.1 patch
            Core::log::report(ERROR, "JamAllocator : unable to find the flag of %p", ptr);
            unlockThreads(mutex);
            return;
        }
        
<<<<<<< HEAD
        _usedSpaces->remove(node, false);
        
        if(_freeSpaces == nullptr || !_freeSpaces->has_data())
            _freeSpaces = node;
        else
            _freeSpaces->add(node);
        
=======
        debugPrint("test2");
        if(_freeSpaces == nullptr || !_freeSpaces->has_data())
        {
            debugPrint("test3");
            _freeSpaces = it.get_node();
        }
        else
        {
            debugPrint("test4");
            _freeSpaces->add(it.get_node());
        }
>>>>>>> almost finishing JamAllocator 2.0.1 patch
        unlockThreads(mutex);
        ptr = nullptr;
    }
}
