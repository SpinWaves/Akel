// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/07/2021
// Updated : 15/09/2023

#ifndef __AK_MEMORY_MANAGER__
#define __AK_MEMORY_MANAGER__

#include <Akpch.h>
#include <Core/Memory/jamAllocator.h>
#include <Core/Memory/fixedAllocator.h>

namespace Ak
{
	namespace Core::memory::internal
	{
		struct AK_API ControlUnit
		{
			std::vector<std::weak_ptr<JamAllocator>> jamStack;
			std::vector<std::weak_ptr<FixedAllocator>> fixedStack;
		};
		void* AK_API alloc(size_t size, bool is_class);
		std::shared_ptr<ControlUnit> AK_API getControlUnit();
		void AK_API dealloc(void* ptr);
	}

	template<typename T, typename ... Args>
	inline T* AK_API memAlloc(Args&& ... args)
	{
		T* ptr = static_cast<T*>(Core::memory::internal::alloc(sizeof(T), std::is_class<T>::value));
		if constexpr(std::is_class<T>::value)
			::new ((void*)ptr) T(std::forward<Args>(args)...);
		return ptr;
	}

	template<typename T = void>
	inline T* AK_API memAllocSize(size_t size)
	{
		return static_cast<T*>(Core::memory::internal::alloc(size, true /* Just to make sure it will be allocated in jam allocator */ ));
	}

	template<typename T>
	inline void AK_API memFree(T* ptr)
	{
		if constexpr(std::is_class<T>::value)
			ptr->~T();
		Core::memory::internal::dealloc(static_cast<void*>(ptr));
	}
}

#endif // __AK_MEMORY_MANAGER__
