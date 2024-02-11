// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/02/2024
// Updated : 09/02/2024

#ifndef __AK_FIXED_ALLOCATOR__
#define __AK_FIXED_ALLOCATOR__

#include <Core/PreCompiled.h>
#include <Utils/BitsArray.h>

namespace Ak
{
	class AK_CORE_API FixedAllocator
    {
		public:
			FixedAllocator() = default;

			void Init(std::size_t blockSize, std::size_t numBlocks);
			void Resize(std::size_t numBlocks);
			bool Contains(void* ptr) const;
			void Destroy();

			inline void AutoResize(bool set) { m_auto_resize = set; }
			inline bool CanAlloc() { return m_bits.GetFirstTrueBit() != (std::size_t)-1; }
			inline constexpr bool IsInit() noexcept { return m_heap != nullptr; }

			template<typename T = void, typename ... Args>
			T* Alloc(Args&& ... args);

			template<typename T = void>
			T* AllocSize(std::size_t size);

			template<typename T = void>
			void Free(T* ptr);

			~FixedAllocator();

		private:
			std::mutex m_mutex;
			
			BitsArray m_bits;
			
			void* m_heap = nullptr;
			std::size_t m_block_size = 0;
			std::size_t m_heap_size = 0;
			int m_allocator_number = 0;
			bool m_auto_resize = false;
    };
}

#include <Core/Memory/FixedAllocator.inl>

#endif
