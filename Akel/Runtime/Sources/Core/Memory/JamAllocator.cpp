// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/02/2024
// Updated : 07/02/2024

#include <Core/Logs.h>
#include <Core/Memory/JamAllocator.h>
#include <Core/Memory/MemoryManager.h>

namespace Ak
{
	void JamAllocator::Init(std::size_t size)
	{
		std::unique_lock<std::mutex> watchdog(m_general_mutex);
		if(m_heap != nullptr)
			return;
		m_heap = std::malloc(size);
		if(!m_heap)
			FatalError("JamAllocator : unable to allocate memory space for an allocator");

		m_heap_size = size;
		m_heap_end = (void*)(reinterpret_cast<std::uintptr_t>(m_heap) + m_heap_size);

		auto control_unit = Core::Memory::Internal::GetControlUnit();
		control_unit->jam_stack.push_back(weak_from_this());
	}

	void JamAllocator::IncreaseSize(std::size_t size)
	{
		if(size < m_heap_size)
		{
			Warning("JamAllocator : Akel's JamAllocators cannot reduce their size");
			return;
		}

		std::unique_lock<std::mutex> watchdog(m_general_mutex);

		if(size > m_heap_size)
		{
			m_resises.push_back(std::make_pair(std::malloc(size - m_heap_size), size - m_heap_size));
			m_heap_size = size;
		}
	}

	void JamAllocator::Destroy()
	{
		std::unique_lock<std::mutex> watchdog(m_general_mutex);
		if(m_heap == nullptr)
			return;
		std::free(m_heap);
		m_heap = nullptr;
		m_heap_end = nullptr;
		m_heap_size = 0;
	}

	void* JamAllocator::InternalAlloc(std::size_t size)
	{
		if(m_heap == nullptr)
		{
			FatalError("Jam Allocator: you need to initialize the allocator before asking him to give you memory");
			return nullptr;
		}
		if(!CanHold(size))
		{
			//if(_autoResize)
			//    increase_size(_heapSize * (4/3));
			//else
			{
				Error("Jam Allocator: the requested allocation is too large for the allocator (% > %), free up memory or increase the size of the allocator", size, m_heap_size - m_mem_used);
				return nullptr;
			}
		}

		void* ptr = nullptr;

		std::unique_lock<std::mutex> watchdog(m_alloc_mutex);

		if(!m_free_spaces.empty())
		{
			auto it = m_free_spaces.lower_bound(size);
			if(it != m_free_spaces.end())
			{
				JamAllocator::flag flag = it->first;
				ptr = it->second;
				m_free_spaces.erase(it);
				if(ptr != nullptr)
					m_used_spaces.emplace(std::make_pair(flag, ptr));
			}
		}

		if(ptr == nullptr)
		{
			JamAllocator::flag flag = size;
			ptr = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(m_heap) + m_mem_used);
			m_used_spaces.emplace(std::make_pair(flag, ptr));
			m_mem_used += size;
		}

		watchdog.unlock();

		if(ptr == nullptr)
			Error("JamAllocator : unable to allocate % bytes", size);

		return ptr;
	}

	void JamAllocator::InternalFree(void* ptr)
	{
		std::unique_lock<std::mutex> watchdog(m_free_mutex);
		std::uint32_t cache;
		std::uint32_t better_flag = -1;
		JamAllocator::flag flag;
		auto iterator = m_used_spaces.end();

		for(auto it = m_used_spaces.begin(); it != m_used_spaces.end(); ++it)
		{
			if((cache = reinterpret_cast<std::uintptr_t>(ptr) - reinterpret_cast<std::uintptr_t>(it->second)) >= 0)
			{
				if(cache < better_flag)
				{
					flag = it->first;
					iterator = it;
					better_flag = cache;
				}
				if(better_flag == 0) // we found the exact flag
					break;
			}
		}

		if(iterator == m_used_spaces.end())
		{
			Error("JamAllocator : unable to find the flag of %", ptr);
			watchdog.unlock();
			return;
		}

		m_used_spaces.erase(iterator);
		m_free_spaces.emplace(std::make_pair(flag, ptr));
	}

	JamAllocator::~JamAllocator()
	{
		Destroy();
	}
}
