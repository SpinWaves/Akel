// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/07/2021
// Updated : 08/09/2023

#ifndef __AK_MEMORY_MANAGER__
#define __AK_MEMORY_MANAGER__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak
{
	namespace Core::memory::internal
	{
		void* alloc(size_t size, bool is_class);
		std::shared_ptr<struct ControlUnit> getControlUnit();
		void dealloc(void* ptr);
	}

    template<typename T, typename ... Args>
    inline T* memAlloc(Args&& ... args)
	{
		T* ptr = Core::memory::internal::alloc(sizeof(T), std::is_class<T>::value);
        if constexpr(std::is_class<T>::value)
            ::new ((void*)ptr) T(std::forward<Args>(args)...);
		return ptr;
	}

    template<typename T>
    inline T* memAllocSize(size_t size) { return Core::memory::internal::alloc(size, std::is_class<T>::value); }

    template<typename T>
    inline void memFree(T* ptr)
	{
        if constexpr(std::is_class<T>::value)
            ptr->~T();
		Core::memory::internal::free(static_cast<void*>(ptr));
	}
}

#endif // __AK_MEMORY_MANAGER__
