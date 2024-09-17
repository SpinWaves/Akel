// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Core/Memory/FixedAllocator.h>
#include <Core/Memory/MemoryManager.h>
#include <Core/Logs.h>

namespace Ak
{
	void FixedAllocator::Init(std::size_t block_size, std::size_t num_blocks)
	{
		if(m_heap != nullptr)
			return;

		std::size_t size = block_size * num_blocks;

		std::unique_lock<std::mutex> watchdog(m_mutex);

		m_heap = std::malloc(size); // Main allocation

		m_block_size = block_size;
		m_heap_size = size;
		m_bits.Init(num_blocks);

		auto control_unit = Core::Memory::Internal::GetControlUnit();
		m_allocator_number = control_unit->fixed_stack.size();
		control_unit->fixed_stack.emplace_back(std::make_pair(this, true));
	}

	void FixedAllocator::Resize(std::size_t num_blocks)
	{
	}

	bool FixedAllocator::Contains(void* ptr) const
	{
		const std::uintptr_t ptr_address = reinterpret_cast<std::uintptr_t>(ptr);
		const std::uintptr_t start_address = reinterpret_cast<std::uintptr_t>(m_heap);
		const std::uintptr_t end_address = reinterpret_cast<std::uintptr_t>(m_heap) + m_heap_size;
		return ptr_address > start_address && ptr_address < end_address;
	}

	void FixedAllocator::Destroy()
	{
		std::unique_lock<std::mutex> watchdog(m_mutex);
		if(m_heap == nullptr)
			return;
		std::free(m_heap);
		m_heap = nullptr;
		m_heap_size = 0;
		auto control_unit = Core::Memory::Internal::GetControlUnit();
		auto it = std::find_if(control_unit->fixed_stack.begin(), control_unit->fixed_stack.end(), [this](auto& pair) { return pair.first == this; });
		if(it == control_unit->fixed_stack.end())
			Error("FixedAllocator : unable to find itself in the memory manager control unit, this should not happen");
		else
			it->second = false;
	}

	FixedAllocator::~FixedAllocator()
	{
		Destroy();
	}
}
