// This file is a part of the Akel editor
// CREATED : 20/07/2021
// UPDATED : 25/07/2021

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

    namespace internalJam
    {
        static MutexHandel mutex;
    }

    class JamAllocator
    {
        public:
            JamAllocator() = default;

            void init(size_t Size);
            void collect();
            bool contains(void* ptr);
            bool canHold(size_t Size);
            void autoResize(bool set);
            void resize(size_t Size);
            void destroy();

            template <typename T = void, typename ... Args>
            T* alloc(Args&& ... args);

            template <typename T = void>
            void free(T* ptr);

            ~JamAllocator();

        private:
            Block* _usedDesc = nullptr;
            Block* _freeDesc = nullptr;
            Ak_uint _nMaxDesc = 0;
            Ak_uint _nUsedDesc = 0;
            Ak_uint _nFreeDesc = 0;
            size_t _heapSize = 0;
            size_t _memUsed = 0;
            void* _end = nullptr;
            void* _heap = nullptr;
            bool _autoResize = false;
    };
}

#include <Core/Memory/jamAllocator.inl>

#endif // __AK_JAM_ALLOCATOR__
