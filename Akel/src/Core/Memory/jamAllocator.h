// This file is a part of Akel
// CREATED : 20/07/2021
// UPDATED : 23/11/2021

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
            bool contains(void* ptr);
            bool canHold(size_t Size);
            void auto_increase_size(bool set);
            void increase_size(size_t Size);
            void destroy();
            inline bool is_init() const { return _heap != nullptr; }

            template <typename T = void, typename ... Args>
            T* alloc(Args&& ... args);

            template <typename T = void>
            void free(T* ptr);

            ~JamAllocator();

        private:

            struct flag
            {
                unsigned int size = 0;
                unsigned int offset = 0;
            };

            size_t _heapSize = 0;
            size_t _memUsed = 0;
            std::vector<std::pair<void*, unsigned int>> _resises;

            void* _heap = nullptr;
            void* _heapEnd = nullptr;

            bool _autoResize = false;
            int _allocator_number = 0;
            std::vector<flag*> _freeSpaces;
            std::vector<flag*> _usedSpaces;

            inline static MutexHandel mutex;
    };
}

#include <Core/Memory/jamAllocator.inl>

#endif // __AK_JAM_ALLOCATOR__
