// This file is a part of Akel
// CREATED : 09/09/2021
// UPDATED : 13/09/2021

#ifndef __AK_UNIQUE_PTR_WRAPPER__
#define __AK_UNIQUE_PTR_WRAPPER__

#include <Akpch.h>
#include <Core/core.h>

namespace Ak
{
    /**
     * Using a struct as a deleter requires as much memory as using a lambda expression (without std::function).
     * Because of this, the unique_ptr has the same size as a raw pointer (8 bytes for 64-bit systems)
     */
    template <typename T>
    struct unique_ptr_w_deleter
    {
        void operator()(T* ptr)
        {
            void* address = ptr;
            custom_free(ptr);

            #ifdef AK_UNIQUE_PTR_WRAPPER_DEBUG_MESSAGE_ENABLED
                Core::log::report(MESSAGE, "unique_ptr_w : pointer freed %p", address);
            #endif

            address = nullptr;
        }
    };

    template <typename T>
    using unique_ptr_w = std::unique_ptr<T, unique_ptr_w_deleter<T>>;

    template <typename T>
    unique_ptr_w<T> make_unique_ptr_w(T* ptr) noexcept
    {
        if(ptr)
            return unique_ptr_w<T>(ptr);
        return unique_ptr_w<T>(nullptr);
    }
}

#endif // __AK_UNIQUE_PTR_WRAPPER__
