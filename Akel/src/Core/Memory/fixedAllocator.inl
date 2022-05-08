// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/08/2021
// Updated : 08/05/2022

#include <Core/log.h>

namespace Ak
{
    template <typename T = void, typename ... Args>
    T* FixedAllocator::alloc(Args&& ... args)
    {
        if(!canAlloc())
        {
            if(_autoResize)
                resize(_bits.size() * 2);
            else
            {
                Core::log::report(ERROR, "Fixed Allocator: unable to alloc block, no more block free");
                return nullptr;
            }
        }

        std::lock_guard<std::mutex> watchdog(_mutex);

        *_it = true;

        if(std::is_class<T>::value)
        {
            T* ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _block_size * (std::distance(_it, _bits.rend()) - 1));
            ::new ((void*)ptr) T(std::forward<Args>(args)...);

            return ptr;
        }

        return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _block_size * (std::distance(_it, _bits.rend()) - 1));
    }

    template <typename T = void>
    void FixedAllocator::free(T* ptr)
    {
        if(!contains(ptr))
        {
            Core::log::report(WARNING, "Fixed Allocator: a pointer allocated by another allocator will be freed, this may be an error");
            delete ptr;
            return;
        }

        std::lock_guard<std::mutex> watchdog(_mutex);

        if(std::is_class<T>::value)
            ptr->~T();

        const size_t index = (reinterpret_cast<uintptr_t>(ptr) - reinterpret_cast<uintptr_t>(_heap)) / _block_size;
        _bits[index] = false;
    }
}
