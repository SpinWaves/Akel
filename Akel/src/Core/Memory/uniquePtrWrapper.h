// This file is a part of Akel
// CREATED : 09/09/2021
// UPDATED : 11/09/2021

#ifndef __AK_UNIQUE_PTR_WRAPPER__
#define __AK_UNIQUE_PTR_WRAPPER__

#include <Akpch.h>
#include <Core/Memory/memoryManager.h>

namespace Ak
{
    template <typename T>
    class unique_ptr_w
    {
        private:
            /**
             * Using a struct as a deleter requires as much memory as using a lambda expression (without std::function).
             * Because of this, the unique_ptr has the same size as a raw pointer (8 bytes for 64-bit systems)
             */
            struct deleter
            {
                void operator()(T* ptr)
                {
                    custom_free(ptr);
                }
            };
            std::unique_ptr<T, deleter> _pointer;

        public:
            unique_ptr_w() = default;
            explicit unique_ptr_w(T* ptr) : _pointer(ptr) {}
            unique_ptr_w(unique_ptr_w& src) = delete; // unique_ptr is a type reserved for movement only
            unique_ptr_w(unique_ptr_w&& src) : _pointer(src.get_native_unique_ptr()) {}
            unique_ptr_w& operator=(unique_ptr_w&& ptr) { _pointer = std::move(ptr.get_native_unique_ptr()); return *this; }

            T* get() { return _pointer.get(); }
            std::unique_ptr<T, deleter>& get_native_unique_ptr() { return _pointer; }
            operator bool() const { return _pointer(); }
            T* release() { return _pointer.release(); }
            void reset(T* ptr) { _pointer.reset(ptr); }
            void reset() { _pointer.reset(); }
            void swap(unique_ptr_w& x) { _pointer.swap(x); }

            T* operator ->() { return get(); }
            typename std::add_lvalue_reference<T>::type operator*() const { return *get(); }

            ~unique_ptr_w() = default;
    };

    template <typename T>
    unique_ptr_w<T> make_unique_ptr_w(T* ptr) noexcept
    {
        if(ptr)
            return unique_ptr_w<T>(ptr);
        return unique_ptr_w<T>(nullptr);
    }
}

#endif // __AK_UNIQUE_PTR_WRAPPER__
