// This file is a part of Akel
// CREATED : 09/09/2021
// UPDATED : 09/09/2021

#ifndef __AK_UNIQUE_PTR_WRAPPER__
#define __AK_UNIQUE_PTR_WRAPPER__

#include <Akpch.h>
#include <Core/Memory/fixedAllocator.h>
#include <Core/Memory/jamAllocator.h>
#include <Core/Memory/memoryHelper.h>

/*
 *  WARNING ! THIS PART IS IN TEST AND NEEDS MORE WORK ! You can use it but be careful
 */

namespace Ak
{
    namespace internal
    {
        template <typename T>
        auto jam_destr = [](T* ptr, JamAllocator& allocator){ allocator.free(ptr) };
        template <typename T>
        auto fixe_destr = [](T* ptr, FixedAllocator& allocator){ allocator.free(ptr) };
        template <typename T>
        auto def_destr = [](T* ptr){ custom_free(ptr) };
    }

    template <typename T>
    using unique_ptr_w = std::unique_ptr<T, decltype(internal::def_destr)>;
    template <typename T>
    using unique_ptr_w_jam = std::unique_ptr<T, decltype(internal::jam_destr)>;
    template <typename T>
    using unique_ptr_w_fixed = std::unique_ptr<T, decltype(internal::fixe_destr)>;

    template <typename T>
    unique_ptr_w_fixed<T> make_unique_fixed(T* ptr, FixedAllocator& allocator)
    {
        if(allocator.contains(ptr))
            return unique_ptr_w_fixed<T>(ptr, fixe_destr(ptr, allocator));
        Core::log::report(WARNING, "unique pointer FixedAllocator wrapper: a pointer allocated by another allocator than the given one has been passed, the unique_ptr returned will contain a nullptr");
        return std::unique_ptr_w_fixed<T>(nullptr, fixe_destr(nullptr, allocator));
    }

    template <typename T>
    unique_ptr_w_jam<T> make_unique_jam(T* ptr, JamAllocator& allocator)
    {
        if(allocator.contains(ptr))
            return unique_ptr_w_jam<T>(ptr, jam_destr(ptr, allocator));
        Core::log::report(WARNING, "unique pointer JamAllocator wrapper: a pointer allocated by another allocator than the given one has been passed, the unique_ptr returned will contain a nullptr");
        return std::unique_ptr_w_jam<T>(nullptr, jam_destr(nullptr, allocator));
    }

    template <typename T>
    unique_ptr_w<T> make_unique_default(T* ptr)
    {
        if(ptr)
            return unique_ptr_w<T>(ptr, def_destr(ptr));
        return std::unique_ptr_w<T>(nullptr, def_destr(nullptr));
    }
}

#endif // __AK_UNIQUE_PTR_WRAPPER__
