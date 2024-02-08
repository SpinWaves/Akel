// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 08/02/2024

#pragma once
#include <Core/Memory/MemoryManager.h>

namespace Ak
{
	template<typename T, typename ... Args>
	inline T* MemAlloc(Args&& ... args)
	{
		T* ptr = static_cast<T*>(Core::Memory::Internal::Alloc(sizeof(T), std::is_class_v<T>));
		if constexpr(std::is_class_v<T>)
			::new ((void*)ptr) T(std::forward<Args>(args)...);
		return ptr;
	}

	template<typename T>
	inline T* MemAllocSize(std::size_t size)
	{
		return static_cast<T*>(Core::Memory::Internal::Alloc(size, true /* Just to make sure it will be allocated in jam allocator */ ));
	}

	template<typename T>
	inline void MemFree(T* ptr)
	{
		if constexpr(std::is_class_v<T>)
			ptr->~T();
		Core::Memory::Internal::Dealloc(static_cast<void*>(ptr));
	}
}
