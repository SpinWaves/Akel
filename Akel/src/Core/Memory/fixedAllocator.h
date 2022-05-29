// This file is a part of Akel
// Authors : @kbz_8
// Created : 18/07/2021
// Updated : 29/05/2022

#ifndef __AK_FIXED_ALLOCATOR__
#define __AK_FIXED_ALLOCATOR__

#include <Akpch.h>
#include <Utils/Containers/bst.h>

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

            template <class T = void, typename ... Args>
            T* alloc(Args&& ... args);

            template <class T = void>
            void free(T* ptr);

            ~FixedAllocator();

        private:
            size_t _block_size = 0;
        	size_t _heap_size = 0;
            void* _heap = nullptr;
            std::vector<bool> _bits;
            bool _autoResize = false;
            std::vector<bool>::reverse_iterator _it;
            std::mutex _mutex;
            int _allocator_number = 0;
    };
}

#include <Core/Memory/fixedAllocator.inl>

#endif // __AK_FIXED_ALLOCATOR__
