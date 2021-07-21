// This file is a part of the Akel editor
// CREATED : 20/07/2021
// UPDATED : 21/07/2021

#ifndef __AK_JAM_ALLOCATOR__
#define __AK_JAM_ALLOCATOR__

#include <Akpch.h>
#include <Utils/utils.h>

namespace Ak
{
    struct Block
    {
        Ak_uint offset;
        Ak_uint size;
    };

    class JamAllocator
    {
        public:
            JamAllocator() = default;

            void init(size_t Size);
            void* alloc(size_t Size);
            void free(void* ptr);
            void collect();
            void resize(size_t Size);
            void destroy();

            ~JamAllocator();


            Block* _usedDesc = nullptr;
            Block* _freeDesc = nullptr;
            Ak_uint _nMaxDesc = 0;
            Ak_uint _nUsedDesc = 0;
            Ak_uint _nFreeDesc = 0;
            size_t _heapSize = 0;
            size_t _memUsed = 0;
            void* _end = nullptr;
            void* _heap = nullptr;
    };
}

#endif // __AK_JAM_ALLOCATOR__
