// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/09/2021
// Updated : 12/05/2022

#ifndef __AK_Unique_ptrRAPPER__
#define __AK_Unique_ptrRAPPER__

#include <Core/projectFile.h>

namespace Ak
{
    void Message(std::string message, ...);
    template <typename T>
    void memFree(T*);
    template <typename T, typename ... Args>
    T* memAlloc(Args&& ... args);

    template <typename T>
    class Unique_ptr
    {
        public:
            constexpr Unique_ptr() noexcept {}
            constexpr Unique_ptr(std::nullptr_t) noexcept {}
            explicit Unique_ptr(T* ptr) noexcept
            {
                if(_ptr != nullptr)
                    memFree(_ptr);
                _ptr = ptr;
            }
            Unique_ptr(Unique_ptr&& ptr) noexcept
            {
                if(_ptr != nullptr)
                    memFree(_ptr);
                _ptr = ptr._ptr;
                ptr._ptr = nullptr;
            }
            Unique_ptr(const Unique_ptr& ptr) = delete;

            inline T* get() noexcept { return _ptr; }

            inline void swap(const Unique_ptr<T>& ptr) noexcept
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

            inline Unique_ptr& operator=(Unique_ptr&& ptr) noexcept
            {
                reset(ptr.release());
                return *this;
            }

            inline Unique_ptr& operator=(std::nullptr_t) noexcept { reset(nullptr); }
            inline Unique_ptr& operator=(const Unique_ptr&) = delete;

            inline T* operator->() const noexcept { return _ptr; }
            inline T& operator*() const noexcept { return *_ptr; }

            ~Unique_ptr()
            {
                if(_ptr != nullptr)
                    memFree(_ptr);
            }

        private:
            T* _ptr = nullptr;
    };

    template <typename T>
    inline Unique_ptr<T> make_Unique_ptr(T* ptr) noexcept { return Unique_ptr<T>(ptr); }

    template <typename T = void, typename ... Args>
    inline Unique_ptr<T> create_Unique_ptr(Args&& ... args) noexcept { return make_Unique_ptr<T>(memAlloc<T>(std::forward<Args>(args)...)); }
}

#endif // __AK_Unique_ptrRAPPER__
