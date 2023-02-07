// This file is a part of Akel
// Authors : @kbz_8
// Created : 18/07/2021
// Updated : 27/01/2023

#ifndef __AK_FIXED_ALLOCATOR__
#define __AK_FIXED_ALLOCATOR__

#include <Akpch.h>
#include <Utils/bits_array.h>
#include <Core/profile.h>

namespace Ak
{
    class AK_API FixedAllocator : public std::enable_shared_from_this<FixedAllocator>
    {
		public:
			FixedAllocator() = default;

			void init(size_t blockSize, size_t numBlocks);
			void resize(size_t numBlocks);
			bool contains(void* ptr) const;
			void destroy();

			inline void autoResize(bool set) { _autoResize = set; }
			inline bool canAlloc() { return _bits.getFirstTrueBit() != (size_t)-1; }
			inline constexpr bool is_init() noexcept { return _heap != nullptr; }

			template <class T = void, typename ... Args>
			T* alloc(Args&& ... args);

			template <class T = void>
			void free(T* ptr);

			~FixedAllocator();

		private:
			std::mutex _mutex;
			BitsArray _bits;
			void* _heap = nullptr;
			size_t _block_size = 0;
			size_t _heap_size = 0;
			int _allocator_number = 0;
			bool _autoResize = false;
    };
}

#include <Core/Memory/fixedAllocator.inl>

#endif // __AK_FIXED_ALLOCATOR__