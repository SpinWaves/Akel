// This file is a part of Akel
// CREATED : 25/07/2021
// UPDATED : 02/08/2021

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
        if(!canHold(sizeof(T*)))
        {
            if(_autoResize)
                resize(_heapSize * 2);
            else
            {
                Core::log::report(ERROR, "Jam Allocator: the requested allocation is too large for the allocator, free up memory or increase the size of the allocator");
                return nullptr;
            }
        }

        lockThreads(mutex);

        T* ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed + sizeof(T*));

        unlockThreads(mutex);

        _memUsed += sizeof(T*);

        if(std::is_class<T>::value)
            ::new ((void*)ptr) T(std::forward<Args>(args)...);

    	return ptr;
    }

    template <typename T = void>
    void JamAllocator::free(T* ptr)
    {
        if(!contains((void*)ptr))
        {
            Core::log::report(ERROR, "Jam Allocator: a pointer allocated by another allocator cannot be freed");
            return;
        }
        if(std::is_class<T>::value)
            ptr->~T();

        lockThreads(mutex);

		if(_memUsed == 0)
		{
            Core::log::report(ERROR, "Jam Allocator: Reached maximum number of FREE descriptors, defragmenting");

            unlockThreads(mutex);
            return;
		}
        _memUsed -= sizeof(T);
        ptr = nullptr;

        unlockThreads(mutex);
    }
}
