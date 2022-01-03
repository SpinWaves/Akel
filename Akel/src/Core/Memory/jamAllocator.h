// This file is a part of Akel
// CREATED : 20/07/2021
// UPDATED : 03/01/2022

#ifndef __AK_JAM_ALLOCATOR__
#define __AK_JAM_ALLOCATOR__

#include <Akpch.h>
#include <Utils/utils.h>

/**
 * TODO :
 *  - Resize system
 *  - Size allocation (like malloc)
 */

namespace Ak
{
    template <typename T>
    class BinarySearchTree;

    class JamAllocator : public std::enable_shared_from_this<JamAllocator>
    {
        public:
            JamAllocator();

            void init(size_t Size);
            inline bool contains(void* ptr);
            inline bool canHold(size_t Size);
            inline void auto_increase_size(bool set);
            void increase_size(size_t Size);
            void destroy();
            inline constexpr bool is_init() noexcept { return _heap != nullptr; }

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
                inline constexpr friend bool operator< (const flag& a, const flag& b) noexcept { return a.size < b.size; }
                inline constexpr friend bool operator> (const flag& a, const flag& b) noexcept { return a.size > b.size; }
                inline constexpr friend bool operator== (const flag& a, const flag& b) noexcept { return a.size == b.size; }
            };

            size_t _heapSize = 0;
            size_t _memUsed = 0;
            std::vector<std::pair<void*, unsigned int>> _resises;

            void* _heap = nullptr;
            void* _heapEnd = nullptr;

            bool _autoResize = false;
            int _allocator_number = 0;
            std::unique_ptr<BinarySearchTree<flag&>> _freeSpaces;
            std::unique_ptr<BinarySearchTree<flag&>> _usedSpaces;

            inline static MutexHandel mutex;
    };
}

#include <Core/Memory/jamAllocator.inl>

#endif // __AK_JAM_ALLOCATOR__
