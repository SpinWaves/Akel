// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/02/2024
// Updated : 08/02/2024

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
		control_unit->fixed_stack.emplace_back(weak_from_this());
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
		if(m_heap == nullptr)
			return;

		std::unique_lock<std::mutex> watchdog(m_mutex);

		std::free(m_heap);
		m_heap = nullptr;
	}

	FixedAllocator::~FixedAllocator()
	{
		Destroy();
	}
}
