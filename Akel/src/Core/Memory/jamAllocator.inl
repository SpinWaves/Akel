// This file is a part of Akel
// Authors : @kbz_8
// Created : 25/07/2021
// Updated : 01/06/2022

#include <Maths/maths.h>

namespace Ak
{
    void FatalError(std::string message, ...);
    void Error(std::string message, ...);
    void Warning(std::string message, ...);

    template <class T, typename ... Args>
    T* JamAllocator::alloc(Args&& ... args)
    {
        if(_heap == nullptr)
        {
            FatalError("Jam Allocator: you need to initialize the allocator before asking him to give you memory");
            return nullptr;
        }
        size_t sizeType = sizeof(T);
        if(!canHold(sizeType))
        {
            //if(_autoResize)
            //    increase_size(_heapSize * (4/3));
            //else
            {
                FatalError("Jam Allocator: the requested allocation is too large for the allocator (%d > %d), free up memory or increase the size of the allocator", sizeType, _heapSize - _memUsed);
                return nullptr;
            }
        }

        T* ptr = nullptr;
        JamAllocator::flag finder;
        finder.size = sizeType;
        BinarySearchTree<JamAllocator::flag*>* node = nullptr;

        std::unique_lock<std::mutex> watchdog(_mutex, std::try_to_lock);

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
            _memUsed += sizeof(_freeSpaces);

            node = reinterpret_cast<BinarySearchTree<JamAllocator::flag*>*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // New Node
            init_node(node, flag);

            if(_usedSpaces == nullptr || !_usedSpaces->has_data())
                _usedSpaces = node;
            else
                _usedSpaces->add(node); // Give node to Used Spaces Tree
            ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // Allocate Pointer
            _memUsed += sizeType;
        }

        watchdog.unlock();

        if(std::is_class<T>::value)
            ::new ((void*)ptr) T(std::forward<Args>(args)...);


    	return ptr;
    }

    template <class T>
    T* JamAllocator::alloc(size_t size)
    {
        if(_heap == nullptr)
        {
            FatalError("Jam Allocator: you need to initialize the allocator before asking him to give you memory");
            return nullptr;
        }
        if(!canHold(size))
        {
            //if(_autoResize)
            //    increase_size(_heapSize * (4/3));
            //else
            {
                FatalError("Jam Allocator: the requested allocation is too large for the allocator (%d > %d), free up memory or increase the size of the allocator", size, _heapSize - _memUsed);
                return nullptr;
            }
        }

        T* ptr = nullptr;
        JamAllocator::flag finder;
        finder.size = size;
        BinarySearchTree<JamAllocator::flag*>* node = nullptr;

        std::unique_lock<std::mutex> watchdog(_mutex, std::try_to_lock);

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
            flag->size = size;
            _memUsed += sizeof(JamAllocator::flag);
            _memUsed += sizeof(_freeSpaces);

            node = reinterpret_cast<BinarySearchTree<JamAllocator::flag*>*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // New Node
            init_node(node, flag);

            if(_usedSpaces == nullptr || !_usedSpaces->has_data())
                _usedSpaces = node;
            else
                _usedSpaces->add(node); // Give node to Used Spaces Tree
            ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed); // Allocate Pointer
            _memUsed += size;
        }

        watchdog.unlock();

        return ptr;
    }

    template <class T>
    void JamAllocator::free(T* ptr)
    {
        if(ptr == nullptr)
        {
            Warning("Jam Allocator: you cannot free a nullptr");
            return;
        }
        if(_heap == nullptr)
        {
            Warning("Jam Allocator: trying to free a pointer with an uninitialised allocator");
            return;
        }
        if(!contains((void*)ptr))
        {
            Warning("Jam Allocator: a pointer allocated by another allocator is trying to be freed");
            return;
        }
        if(std::is_class<T>::value)
            ptr->~T();

        JamAllocator::flag* finder = nullptr;
        BinarySearchTree<JamAllocator::flag*>* node = nullptr;
        size_t flag_size = sizeof(JamAllocator::flag);
        unsigned int better_flag = UINT_MAX;

        std::unique_lock<std::mutex> watchdog(_mutex, std::try_to_lock);

        auto it = _usedSpaces->root_it();
        if(!it.has_data()) // used space tree is not supposed to be empty here
        {
            Error("Jam Allocator : an inconsistency was detected when a pointer was freed");
            watchdog.unlock();
            return;
        }

        unsigned int cache = 0;

        for(; it.has_data(); it.next()) // flag finder
        {
            if((cache = reinterpret_cast<uintptr_t>(ptr) - (reinterpret_cast<uintptr_t>(it->getData()) + flag_size)) >= 0)
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

        //std::cout << node << " : " << finder->size << std::endl;

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

        ptr = nullptr;

        watchdog.unlock();
    }
}
