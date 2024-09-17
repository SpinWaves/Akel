// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once
#include <Core/Memory/JamAllocator.h>
#include <Core/Logs.h>

namespace Ak
{
	template<typename T, typename ... Args>
	T* JamAllocator::Alloc(Args&&... args)
	{
		T* ptr = reinterpret_cast<T*>(InternalAlloc(sizeof(T)));
		void* tmp = ptr;
		std::size_t s = std::numeric_limits<std::size_t>::max();
		if constexpr(!std::is_void_v<T>)
		{
			std::align(alignof(T), sizeof(T), tmp, s);
			m_mem_used += reinterpret_cast<std::uintptr_t>(tmp) - reinterpret_cast<std::uintptr_t>(ptr);
		}
		if constexpr(std::is_class_v<T>)
			::new ((void*)ptr) T(std::forward<Args>(args)...);
		return ptr;
	}

	template<typename T>
	T* JamAllocator::AllocSize(size_t size)
	{
		static_assert(!std::is_class_v<T>, "Ak::JamAllocator::AllocSize cannot allocate classes/structs");

		T* ptr = reinterpret_cast<T*>(InternalAlloc(size));
		void* tmp = ptr;
		std::size_t s = std::numeric_limits<std::size_t>::max();
		if constexpr(!std::is_void_v<T>)
		{
			std::align(alignof(T), sizeof(T), tmp, s);
			m_mem_used += reinterpret_cast<std::uintptr_t>(tmp) - reinterpret_cast<std::uintptr_t>(ptr);
		}
		return ptr;
	}

	template<typename T>
	void JamAllocator::Free(T* ptr)
	{
		if(ptr == nullptr)
		{
			Warning("Jam Allocator: you cannot free a nullptr");
			return;
		}
		if(m_heap == nullptr)
		{
			Warning("Jam Allocator: trying to free a pointer with an uninitialised allocator");
			return;
		}
		if(!Contains((void*)ptr))
		{
			Warning("Jam Allocator: a pointer allocated by another allocator is trying to be freed");
			return;
		}
		if constexpr(std::is_class_v<T>)
			ptr->~T();
		InternalFree(ptr);
	}
}
