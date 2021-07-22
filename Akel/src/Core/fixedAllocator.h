// This file is a part of the Akel editor
// CREATED : 18/07/2021
// UPDATED : 22/07/2021

#ifndef __AK_FIXED_ALLOCATOR__
#define __AK_FIXED_ALLOCATOR__

#include <Akpch.h>
#include <Utils/utils.h>

namespace Ak
{
    class FixedAllocator
    {
        public:
            FixedAllocator() = default;

            void init(size_t blockSize, size_t numBlocks);
            void* alloc();
            void free(void* ptr);
            void resize(size_t numBlocks);
            bool contains(void* ptr) const;
            void destroy();

            ~FixedAllocator();

        private:
            size_t _block_size = 0;
            void* _heap = nullptr;
        	size_t _heap_size = 0;
            std::vector<bool> _bits;
    };
}

#endif // __AK_FIXED_ALLOCATOR__
