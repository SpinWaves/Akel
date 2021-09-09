// This file is a part of Akel
// CREATED : 25/07/2021
// UPDATED : 08/09/2021

#include <Core/Memory/jamAllocator.h>

namespace Ak
{
    template <typename T = void, typename ... Args>
    T* JamAllocator::alloc(Args&& ... args)
    {
        if(_heapSize == 0)
        {
            Core::log::report(ERROR, "Jam Allocator: you need to initialize the allocator before aking him to give you memory");
            return nullptr;
        }
        if(!canHold(sizeof(T)))
        {
            if(_autoResize)
                resize(_heapSize * 2);
            else
            {
                Core::log::report(ERROR, "Jam Allocator: the requested allocation is too large for the allocator, free up memory or increase the size of the allocator");
                return nullptr;
            }
        }

        block* finder = _head;
        block* better = nullptr;
        T* ptr = nullptr;

        lockThreads(mutex);

        while(finder != nullptr)
        {
            if(finder->size >= sizeof(T) && finder->is_free)
            {
                if(finder->size == sizeof(T)) // We found a perfect sized block !
                {
                    ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + finder->offset + sizeof(block));
                    break;
                }
                if(better == nullptr)
                    better = finder;
                else if(finder->size < better->size)
                    better = finder;
            }
            finder = finder->next;
        }
        if(ptr == nullptr && better != nullptr)
            ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + finder->offset + sizeof(block));

        block* block_ptr = static_cast<block*>((void*)(reinterpret_cast<uintptr_t>(_heap) + _memUsed));

        unlockThreads(mutex);

        ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed + sizeof(block));
        block_ptr->size = sizeof(T);
        block_ptr->is_free = false;
        block_ptr->offset = _memUsed;
        add_block(block_ptr);

        _memUsed += sizeof(T) + sizeof(block);

        if(std::is_class<T>::value)
            ::new ((void*)ptr) T(std::forward<Args>(args)...);

    	return ptr;
    }

    template <typename T = void>
    void JamAllocator::free(T* ptr)
    {
        if(!contains((void*)ptr))
        {
            Core::log::report(WARNING, "Jam Allocator: a pointer allocated by another allocator will be freed, this may be an error");
            delete ptr;
            return;
        }
        if(std::is_class<T>::value)
            ptr->~T();

        block* finder = _head;
        do
        {
            if(ptr == (void*)((uintptr_t)finder + sizeof(block)))
            {
                finder->is_free = true;
                break;
            }
            finder = finder->next;
        } while(finder != _tail);
        ptr = nullptr;
    }
}
