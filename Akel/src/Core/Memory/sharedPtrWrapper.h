// This file is a part of the Akel editor
// CREATED : 24/07/2021
// UPDATED : 25/07/2021

#ifndef __AK_SHARED_PTR_WRAPPER__
#define __AK_SHARED_PTR_WRAPPER__

#include <Akpch.h>
#include <Core/Memory/fixedAllocator.h>
#include <Core/Memory/jamAllocator.h>
#include <Core/Memory/memoryHelper.h>

namespace Ak
{
    template <typename T>
    std::shared_ptr<T> shared_ptr_w(T* ptr, FixedAllocator& allocator)
    {
        return std::shared_ptr<T>(ptr, [allocator](T* ptr) { allocator.free(ptr); });
    }

    template <typename T>
    std::shared_ptr<T> shared_ptr_w(T* ptr, JamAllocator& allocator)
    {
        return std::shared_ptr<T>(ptr, [allocator](T* ptr) { allocator.free(ptr); });
    }

    template <typename T>
    std::shared_ptr<T> shared_ptr_w(T* ptr)
    {
        return std::shared_ptr<T>(ptr, [](T* ptr) { custom_free(ptr); });
    }
}

#endif // __AK_SHARED_PTR_WRAPPER__
