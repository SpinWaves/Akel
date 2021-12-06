// This file is a part of Akel
// CREATED : 18/07/2021
// UPDATED : 06/12/2021

#ifndef __AK_FIXED_ALLOCATOR__
#define __AK_FIXED_ALLOCATOR__

#include <Akpch.h>
#include <Utils/utils.h>

namespace Ak
{
    class FixedAllocator : public std::enable_shared_from_this<FixedAllocator>
    {
        public:
            FixedAllocator() = default;

            void init(size_t blockSize, size_t numBlocks);
            void resize(size_t numBlocks);
            bool canAlloc();
            bool contains(void* ptr) const;
            void autoResize(bool set);
            void destroy();
            inline constexpr bool is_init() noexcept { return _heap != nullptr; }

            template <typename T = void, typename ... Args>
            T* alloc(Args&& ... args);

            template <typename T = void>
            void free(T* ptr);

            ~FixedAllocator();

        private:
            size_t _block_size = 0;
        	size_t _heap_size = 0;
            void* _heap = nullptr;
            std::vector<bool> _bits;
            bool _autoResize = false;
            std::vector<bool>::reverse_iterator _it;
            inline static MutexHandel mutex;
            int _allocator_number = 0;
    };
}

#include <Core/Memory/fixedAllocator.inl>

#endif // __AK_FIXED_ALLOCATOR__
