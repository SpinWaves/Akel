// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/10/2021
// Updated : 04/05/2022

#ifndef __AK_MUTABLE_STRINGS__
#define __AK_MUTABLE_STRINGS__

#include <Akpch.h>

namespace Ak
{
    class mString
    {
        public:
            struct iterator
            {
                using iterator_category = std::forward_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = const char;
                using pointer           = const char*;
                using reference         = const char&;
            
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

            inline static const size_t npos = -1;

            mString();
            mString(const char* str);
            mString(const mString& str);
            mString(mString&& str);

            mString& operator=(mString str);
            mString& operator=(const char* str);

            inline size_t size()       { return _string.size(); }
            inline size_t length()     { return _string.size(); }
            inline void clear()        { _string.clear(); }
            inline bool empty() const  { return _string.empty(); }

            // Modifiers
            mString& append(mString str);
            mString& append(mString str, size_t subpos, size_t sublen = npos);
            mString& append(const char* str);

            void push_back(char c) { _string.push_back(c); }
            char pop_back();

            // Getters
            char operator[](unsigned int index);
            inline const char* c_str() { return &_string[0]; }

            ~mString() = default;

        private:
            std::vector<char> _string;
    };
}

#endif // __AK_MUTABLE_STRINGS__
