// This file is a part of Akel
<<<<<<< HEAD
// Authors : @kbz_8
// Created : 20/07/2021
// Updated : 24/02/2022
=======
// CREATED : 20/07/2021
// UPDATED : 08/01/2022
>>>>>>> working on path for jamallocator

#ifndef __AK_JAM_ALLOCATOR__
#define __AK_JAM_ALLOCATOR__

#include <Akpch.h>

/**
 * TODO :
 *  - Resize system
 *  - Size allocation (like malloc)
 */

<<<<<<< HEAD
// JamAllocator version 2.0.1
=======
// JamAllocator version 2.0.0
>>>>>>> working on path for jamallocator

namespace Ak
{
    template <typename T>
    class BinarySearchTree;

    class JamAllocator : public std::enable_shared_from_this<JamAllocator>
    {
        public:
            JamAllocator() = default;

            void init(size_t Size);

            inline constexpr bool canHold(size_t Size) noexcept { return Size > _heapSize - _memUsed; }
            inline constexpr void auto_increase_size(bool set) noexcept { _autoResize = set; }
            inline constexpr bool contains(void* ptr) noexcept { return ptr >= _heap && ptr <= _heapEnd; }
            inline constexpr bool is_init() noexcept { return _heap != nullptr; }

            void increase_size(size_t Size);
            void destroy();

            template <typename T = void, typename ... Args>
            T* alloc(Args&& ... args);

            template <typename T = void>
            void free(T* ptr);

            ~JamAllocator();
        
        private:

            struct flag
            {
                unsigned int size = 0;
            };

            size_t _heapSize = 0;
            size_t _memUsed = 0;
            std::vector<std::pair<void*, unsigned int>> _resises;

            void* _heap = nullptr;
            void* _heapEnd = nullptr;

            bool _autoResize = false;
            int _allocator_number = 0;
<<<<<<< HEAD
            BinarySearchTree<flag*>* _freeSpaces = nullptr;
            BinarySearchTree<flag*>* _usedSpaces = nullptr;

<<<<<<< HEAD
            void init_node(BinarySearchTree<flag*>* node, flag* ptr);
=======
            void init_node(BinarySearchTree<flag&>* node, flag& ptr);
>>>>>>> working on path for jamallocator
=======
            BinarySearchTree<const flag&>* _freeSpaces;
            BinarySearchTree<const flag&>* _usedSpaces;

            void init_node(BinarySearchTree<const flag&>* node, const flag& ptr);
>>>>>>> working on a patch for jamallocator

            inline static MutexHandel mutex;
    };
}

#include <Core/Memory/jamAllocator.inl>

#endif // __AK_JAM_ALLOCATOR__
