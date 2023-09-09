// This file is a part of Akel
// Authors : @kbz_8
// Created : 24/07/2021
// Updated : 09/09/2023

#ifndef __AK_SHARED_PTR__
#define __AK_SHARED_PTR__

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
     * Ak::make_shared_w without passing the allocator (even if the raw pointer is declared by
     * another allocator than those of the Memory Manager but not a custom allocator other than 
     * the JamAllocator, FixedAllocator or the new operator). However, the release will be slower
     * because the Memory Manager will check all instantiated allocators to see if the pointer
     * belongs to them, and then free it.
     */

    template <typename T>
    inline std::shared_ptr<T> make_shared_ptr_w(T* ptr) { return std::shared_ptr<T>(ptr, [](T* ptr) { memFree(ptr); }); }

    template <typename T = void, typename ... Args>
    inline std::shared_ptr<T> create_shared_ptr_w(Args&& ... args) noexcept { return make_shared_ptr_w<T>(memAlloc<T>(std::forward<Args>(args)...)); }
}

#endif
