// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/02/2024
// Updated : 09/02/2024

#pragma once

#include <Core/PreCompiled.h>

namespace Ak
{
	class AK_CORE_API JamAllocator
	{
		public:
			JamAllocator() = default;

			void Init(std::size_t size);
			void IncreaseSize(std::size_t size);
			void Destroy();

			inline bool CanHold(std::size_t size) noexcept { return size + m_mem_used < m_heap_size; }
			inline void AutoIncreaseSize(bool set) noexcept { m_auto_resize = set; }
			inline bool Contains(void* ptr) noexcept { return ptr >= m_heap && ptr <= m_heap_end; }
			inline bool IsInit() noexcept { return m_heap != nullptr; }

			template<typename T = void, typename ... Args>
			T* Alloc(Args&& ... args);

			template<typename T = void>
			T* AllocSize(std::size_t size);

			template<typename T = void>
			void Free(T* ptr);

			~JamAllocator();

		private:
			using flag = std::uint64_t;

			void* InternalAlloc(std::size_t size);
			void InternalFree(void* ptr);

		private:
			std::multimap<flag, void*> m_free_spaces;
			std::multimap<flag, void*> m_used_spaces;

			std::vector<std::pair<void*, unsigned int>> m_resises;
			std::mutex m_alloc_mutex;
			std::mutex m_free_mutex;
			std::mutex m_general_mutex;

			void* m_heap = nullptr;
			void* m_heap_end = nullptr;

			std::size_t m_heap_size = 0;
			std::size_t m_mem_used = 0;

			bool m_auto_resize = false;
			int m_allocator_number = 0;
	};
}

#include <Core/Memory/JamAllocator.inl>
