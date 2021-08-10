// This file is a part of Akel
// CREATED : 20/07/2021
// UPDATED : 09/08/2021

#ifndef __AK_JAM_ALLOCATOR__
#define __AK_JAM_ALLOCATOR__

#include <Akpch.h>
#include <Utils/utils.h>

namespace Ak
{
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

            inline static std::vector<JamAllocator*> allAllocs;

        private:
            size_t _heapSize = 0;
            size_t _memUsed = 0;
            std::vector<size_t> _allocOffsets;
            void* _end = nullptr;
            void* _heap = nullptr;
            bool _autoResize = false;

            inline static MutexHandel mutex;
    };
}

#include <Core/Memory/jamAllocator.inl>

#endif // __AK_JAM_ALLOCATOR__
