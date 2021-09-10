// This file is a part of Akel
// CREATED : 09/09/2021
// UPDATED : 10/09/2021

#ifndef __AK_UNIQUE_PTR_WRAPPER__
#define __AK_UNIQUE_PTR_WRAPPER__

#include <Akpch.h>
#include <Core/Memory/fixedAllocator.h>
#include <Core/Memory/jamAllocator.h>
#include <Core/Memory/memoryManager.h>

namespace Ak
{
    template <typename T>
    class unique_ptr_w
    {
        public:
            unique_ptr_w() = default;
            explicit unique_ptr_w(T* ptr);
            unique_ptr_w(unique_ptr_w& src);
            unique_ptr_w(unique_ptr_w&& src);

            T* get() { return _pointer.get(); }
            operator bool() const { return _pointer(); }
            T* release() { return _pointer.release() }
            void reset(T* ptr) { _pointer.reset(ptr) }
            void reset() { _pointer.reset() }
            void swap(unique_ptr_w& x) { _pointer.swap(x) }

            T* operator ->() { return _pointer }
            typename std::add_lvalue_reference<T>::type operator*() const { return *_pointer }
            typename std::add_lvalue_reference<T>::type operator [](size_t i) const { return _pointer[i] }

            ~unique_ptr_w() = default;

        private:
            auto _dest = [](T* ptr) { custom_free(ptr); };
            std::unique_ptr<T, decltype(_dest)> _pointer;
    };

    template <typename T>
    unique_ptr_w<T> make_unique_ptr_w(T* ptr)
    {
        if(ptr)
            return unique_ptr_w<T>(ptr);
        return unique_ptr_w<T>(nullptr);
    }
}

#include <Core/Memory/uniquePtrWrapper.inl>

#endif // __AK_UNIQUE_PTR_WRAPPER__
