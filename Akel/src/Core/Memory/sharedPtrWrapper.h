// This file is a part of Akel
// CREATED : 24/07/2021
// UPDATED : 09/09/2021

#ifndef __AK_SHARED_PTR_WRAPPER__
#define __AK_SHARED_PTR_WRAPPER__

#include <Akpch.h>
#include <Core/Memory/fixedAllocator.h>
#include <Core/Memory/jamAllocator.h>
#include <Core/Memory/memoryHelper.h>

namespace Ak
{
    template <typename T>
    std::shared_ptr<T> make_shared_ptr_w(T* ptr, FixedAllocator& allocator)
    {
        if(allocator.contains(ptr))
            return std::shared_ptr<T>(ptr, [allocator](T* ptr) { allocator.free(ptr); });
        return std::shared_ptr<T>(ptr);
    }

    template <typename T>
    std::shared_ptr<T> make_shared_ptr_w(T* ptr, JamAllocator& allocator)
    {
        if(allocator.contains(ptr))
            return std::shared_ptr<T>(ptr, [allocator](T* ptr) { allocator.free(ptr); });
        return std::shared_ptr<T>(ptr);
    }

    template <typename T>
    std::shared_ptr<T> make_shared_ptr_w(T* ptr)
    {
        if(ptr)
            return std::shared_ptr<T>(ptr, [](T* ptr) { custom_free(ptr); });
        return std::shared_ptr<T>(ptr);
    }
}

#endif // __AK_SHARED_PTR_WRAPPER__
