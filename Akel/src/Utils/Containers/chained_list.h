// This file is a part of Akel
// CREATED : 09/08/2021
// UPDATED : 11/08/2021

#ifndef __AK_CHAINED_LIST__
#define __AK_CHAINED_LIST__

#include <Akpch.h>
#include <Utils/utils.h>
#include <Core/core.h>

namespace Ak
{
    /*
    template <class T>
    struct chained_list
    {
        explicit chained_list(std::initializer_list<T> elements) : _allocator()
        {
            _allocator.init(sizeof(T), 256);
        }

        chained_list& operator= (chained_list&& list)
        {

        }

        void push_back(T element)
        {
            block* new_elem = _allocator.alloc<block>();
            if(!new_elem)
            {
                Core::log::report(ERROR, "Chained list: unable to alloc new element block");
                return;
            }
            new_elem->elem = std::move(element);
            new_elem->next = nullptr;
            new_elem->prev = nullptr;
            if(_tail != nullptr)
            {
                new_elem->prev = _tail;
                _tail->next = new_elem;
            }
            else
                _head = new_elem;
            _tail = new_elem;
        }

        void pop_back(T element)
        {
            if(_head == nullptr || _tail == nullptr)
            {
                Core::log::report(ERROR, "Chained list: there are no element to pop back");
                return;
            }
            block* block_to_free = _tail;
            _tail = _tail->prev;
            _tail->next = nullptr;
            custom_free(block_to_free);
        }

        private:
            struct block
            {
                block* next = nullptr;
                block* prev = nullptr;
                T elem;
            };

            block* _head = nullptr;
            block* _tail = nullptr;
            FixedAllocator _allocator;
    };
    */
}

#endif // __AK_CHAINED_LIST__
