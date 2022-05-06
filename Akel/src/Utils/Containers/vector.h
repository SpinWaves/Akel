// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/05/2021
// Updated : 06/05/2022

#ifndef __AK_VECTOR__
#define __AK_VECTOR__

#include <Akpch.h>
#include <Core/core.h>

namespace Ak
{
    template <typename T>
    class Vector
    {
        public:
            struct iterator
            {
                using iterator_category = std::forward_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = T;
                using pointer           = T*;
                using reference         = T&;
            
                iterator(pointer ptr) : _ptr(ptr) {}
                inline reference operator*() const noexcept { return *_ptr; }
                inline pointer operator->() noexcept { return _ptr; }

                // Prefix increment
                inline iterator& operator++() { _ptr++; return *this; }  

                // Postfix increment
                inline iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

                inline friend bool operator== (const iterator& a, const iterator& b) { return a._ptr == b._ptr; }
                inline friend bool operator!= (const iterator& a, const iterator& b) { return a._ptr != b._ptr; }

                private:
                    pointer _ptr;
            };

            Vector() : _array(nullptr) {}
            Vector(std::initializer_list<T> list);
            
            Vector(std::vector<T> std_vec, size_t begin = 0; size_t end = -1);
            Vector(std::vector<T> std_vec, std::vector<T>::iterator begin, std::vector<T>::iterator end);

            Vector(Vector<T> vec, size_t begin = 0; size_t end = -1);
            Vector(Vector<T> vec, iterator begin, iterator end);

            T& operator[](size_t index) noexcept;
            T& at(size_t index) noexcept;

            void resize(size_t size);
            void reserve(size_t size);

            void clear() noexcept;

            inline size_t size() const noexcept { return _size; }

            void push_back(T&& value);
            void push_back(const T& value);

            void erase(interator begin, iterator end);
            
            void push(T&& value, iterator pos);
            void push(const T& value, iterator pos);

            void push(T&& value, size_t pos);
            void push(const T& value, size_t pos);

            T pop_back();
            
            T pop(iterator pos);
            T pop(size_t pos);

            ~Vector();

        private:
            unique_ptr_w<T> _array;
            size_t _size = 0;
    };
}

#endif // __AK_VECTOR__
