// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/07/2021
// Updated : 17/03/2023

#ifndef __AK_JAM_ALLOCATOR__
#define __AK_JAM_ALLOCATOR__

#include <Akpch.h>
#include <Core/profile.h>

/**
 * TODO :
 *  - Resize system
 */

namespace Ak
{
    class AK_API JamAllocator : public std::enable_shared_from_this<JamAllocator>
    {
        public:
            JamAllocator() = default;

            void init(size_t Size);

            inline bool canHold(size_t Size) noexcept { return Size + _memUsed < _heapSize; }
            inline void auto_increase_size(bool set) noexcept { _autoResize = set; }
            inline bool contains(void* ptr) noexcept { return ptr >= _heap && ptr <= _heapEnd; }
            inline bool is_init() noexcept { return _heap != nullptr; }

            void increase_size(size_t Size);
            void destroy();

            template <class T = void, typename ... Args>
            T* alloc(Args&& ... args);

            template <class T = void>
            T* alloc(size_t size);

            template <class T = void>
            void free(T* ptr);

            ~JamAllocator();
        
        private:
			using flag = int64_t;

			void* internal_allocation(size_t size);
			void internal_free(void* ptr);

			std::multimap<flag, void*> _freeSpaces;
			std::multimap<flag, void*> _usedSpaces;
            
            std::vector<std::pair<void*, unsigned int>> _resises;
            std::mutex _mutex;

            void* _heap = nullptr;
            void* _heapEnd = nullptr;

            size_t _heapSize = 0;
            size_t _memUsed = 0;

            bool _autoResize = false;
            int _allocator_number = 0;
    };
}

#include <Core/Memory/jamAllocator.inl>

#endif // __AK_JAM_ALLOCATOR__
