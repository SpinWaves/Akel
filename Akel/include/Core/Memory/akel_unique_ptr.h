// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/09/2021
// Updated : 09/09/2023

#ifndef __AK_UNIQUE_PTR__
#define __AK_UNIQUE_PTR__

#include <Core/profile.h>

namespace Ak
{
    template <typename T>
    void memFree(T*);
    template <typename T, typename ... Args>
    T* memAlloc(Args&& ... args);

    template <typename T>
    class AK_API UniquePtr
    {
        public:
            constexpr UniquePtr() noexcept {}
            constexpr UniquePtr(std::nullptr_t) noexcept {}
            explicit UniquePtr(T* ptr) noexcept
            {
                if(_ptr != nullptr)
                    memFree(_ptr);
                _ptr = ptr;
            }
            UniquePtr(UniquePtr&& ptr) noexcept
            {
                if(_ptr != nullptr)
                    memFree(_ptr);
                _ptr = ptr._ptr;
                ptr._ptr = nullptr;
            }
            UniquePtr(const UniquePtr& ptr) = delete;

            inline T* get() noexcept { return _ptr; }

            inline void swap(const UniquePtr<T>& ptr) noexcept
            {
                T* temp = _ptr;
                _ptr = ptr._ptr;
                ptr._ptr = temp;
            }

            inline void reset(T* ptr = nullptr) noexcept
            {
                if(_ptr != nullptr)
                    memFree(_ptr);
                _ptr = ptr;
            }

            inline T* release() noexcept
            {
                T* temp = _ptr;
                _ptr = nullptr;
                return temp;
            }

            inline explicit operator bool() const noexcept { return _ptr != nullptr; }

            inline UniquePtr& operator=(UniquePtr&& ptr) noexcept
            {
                reset(ptr.release());
                return *this;
            }

            inline UniquePtr& operator=(std::nullptr_t) noexcept { reset(nullptr); }
            inline UniquePtr& operator=(const UniquePtr&) = delete;

            inline T* operator->() const noexcept { return _ptr; }
            inline T& operator*() const noexcept { return *_ptr; }

            ~UniquePtr()
            {
                if(_ptr != nullptr)
                    memFree(_ptr);
            }

        private:
            T* _ptr = nullptr;
    };

    template <typename T>
    inline UniquePtr<T> makeUniquePtr(T* ptr) noexcept { return UniquePtr<T>(ptr); }

    template <typename T = void, typename ... Args>
    inline UniquePtr<T> createUniquePtr(Args&& ... args) noexcept { return makeUniquePtr<T>(memAlloc<T>(std::forward<Args>(args)...)); }
}

#endif
