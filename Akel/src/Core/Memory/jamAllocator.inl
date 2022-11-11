// This file is a part of Akel
// Authors : @kbz_8
// Created : 25/07/2021
// Updated : 11/11/2022

#include <Maths/maths.h>

namespace Ak
{
    void Error(std::string message, ...);
    void Warning(std::string message, ...);

    template <class T, typename ... Args>
    T* JamAllocator::alloc(Args&& ... args)
    {
		T* ptr = reinterpret_cast<T*>(internal_allocation(sizeof(T)));
        if constexpr(std::is_class<T>::value)
            ::new ((void*)ptr) T(std::forward<Args>(args)...);
    	return ptr;
    }

    template <class T>
    T* JamAllocator::alloc(size_t size)
    {
		return reinterpret_cast<T*>(internal_allocation(size));
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
        if constexpr(std::is_class<T>::value)
            ptr->~T();

        JamAllocator::flag* finder = nullptr;
        BinarySearchTree<JamAllocator::flag*>* node = nullptr;
        size_t flag_size = sizeof(JamAllocator::flag);
        unsigned int better_flag = UINT_MAX;

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
