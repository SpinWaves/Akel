// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/07/2021
// Updated : 09/05/2022

#ifndef __AK_JAM_ALLOCATOR__
#define __AK_JAM_ALLOCATOR__

#include <Akpch.h>

/**
 * TODO :
 *  - Resize system
 *  - Size allocation (like malloc)
 */

// JamAllocator version 2.0.2

namespace Ak
{
    template <typename T>
    class BinarySearchTree;

    class JamAllocator : public std::enable_shared_from_this<JamAllocator>
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

            template <typename T = void, typename ... Args>
            T* alloc(Args&& ... args);

            template <typename T = void>
            T* alloc(size_t size);

            template <typename T = void>
            void free(T* ptr);

            ~JamAllocator();
        
        private:

            struct flag
            {
                unsigned int size = 0;
            };
            
            std::vector<std::pair<void*, unsigned int>> _resises;

            size_t _heapSize = 0;
            size_t _memUsed = 0;

            void* _heap = nullptr;
            void* _heapEnd = nullptr;

            bool _autoResize = false;
            int _allocator_number = 0;
            
            BinarySearchTree<flag*>* _freeSpaces = nullptr;
            BinarySearchTree<flag*>* _usedSpaces = nullptr;

            void init_node(BinarySearchTree<flag*>* node, flag* ptr);

            std::mutex _mutex;
    };
}

#include <Core/Memory/jamAllocator.inl>

#endif // __AK_JAM_ALLOCATOR__
