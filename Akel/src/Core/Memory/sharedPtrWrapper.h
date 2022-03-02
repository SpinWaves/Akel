// This file is a part of Akel
// Author : @kbz_8
// CREATED : 24/07/2021
// UPDATED : 10/09/2021

#ifndef __AK_SHARED_PTR_WRAPPER__
#define __AK_SHARED_PTR_WRAPPER__

#include <Akpch.h>
#include <Core/Memory/fixedAllocator.h>
#include <Core/Memory/jamAllocator.h>
#include <Core/Memory/memoryManager.h>

namespace Ak
{
    template <typename T>
    std::shared_ptr<T> make_shared_ptr_w(T* ptr, FixedAllocator& allocator)
    {
        if(allocator.contains(ptr))
            return std::shared_ptr<T>(ptr, [&allocator](T* ptr) { allocator.free(ptr); });
        return std::shared_ptr<T>(ptr);
    }

    template <typename T>
    std::shared_ptr<T> make_shared_ptr_w(T* ptr, JamAllocator& allocator)
    {
        if(allocator.contains(ptr))
            return std::shared_ptr<T>(ptr, [&allocator](T* ptr) { allocator.free(ptr); });
        return std::shared_ptr<T>(ptr);
    }

    /**
     * Due to the Memory Manager's management of allocators, it is possible to pass through
     * Ak::make_shared_w without passing the allocator (if the raw pointer is declared by
     * another allocator than those of the Memory Manager). However, the release will be slower
     * because the Memory Manager will check all instantiated allocators to see if the pointer
     * belongs to them, and then free it.
     */

    template <typename T>
    std::shared_ptr<T> make_shared_ptr_w(T* ptr)
    {
        if(ptr)
            return std::shared_ptr<T>(ptr, [](T* ptr) { custom_free(ptr); });
        return std::shared_ptr<T>(ptr);
    }
}

#endif // __AK_SHARED_PTR_WRAPPER__
