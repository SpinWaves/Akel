// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once
#include <Core/Memory/FixedAllocator.h>
#include <Core/Logs.h>

namespace Ak
{
	template<typename T, typename ... Args>
	T* FixedAllocator::Alloc(Args&& ... args)
	{
		if(!CanAlloc())
		{
//			if(!m_auto_resize)
			{
				Error("Fixed Allocator: unable to alloc block, no more block free");
				return nullptr;
			}
		}
		if(sizeof(T) > m_block_size)
		{
			Error("Fixed Allocator: unable to alloc block (size required is greater than a block size, %)", sizeof(T));
			return nullptr;
		}
		std::unique_lock<std::mutex> watchdog(m_mutex);
		std::size_t index = m_bits.GetFirstTrueBit();
		m_bits.Set(index, 0);
		watchdog.unlock();
		if constexpr(std::is_class_v<T>)
		{
			T* ptr = reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(m_heap) + m_block_size * index);
			::new ((void*)ptr) T(std::forward<Args>(args)...);
			return ptr;
		}
		return reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(m_heap) + m_block_size * index);
	}

	template<typename T>
	T* FixedAllocator::AllocSize(size_t size)
	{
		if(!CanAlloc())
		{
//			if(!m_auto_resize)
			{
				Error("Fixed Allocator: unable to alloc block, no more block free");
				return nullptr;
			}
		}
		if(size > m_block_size)
		{
			Error("Fixed Allocator: unable to alloc block (size required is greater than a block size, %)", size);
			return nullptr;
		}
		std::unique_lock<std::mutex> watchdog(m_mutex);
		std::size_t index = m_bits.GetFirstTrueBit();
		m_bits.Set(index, 0);
		return reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(m_heap) + m_block_size * index);
	}

	template<typename T>
	void FixedAllocator::Free(T* ptr)
	{
		if(!Contains(ptr))
		{
			Warning("Fixed Allocator: a pointer allocated by another allocator will be freed, this may be an error");
			return;
		}
		if constexpr(std::is_class_v<T>)
			ptr->~T();
		const size_t index = (reinterpret_cast<std::uintptr_t>(ptr) - reinterpret_cast<std::uintptr_t>(m_heap)) / m_block_size;
		std::unique_lock<std::mutex> watchdog(m_mutex);
		m_bits.Set(index, 1);
	}
}
