// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/10/2021
// Updated : 29/04/2022

#ifndef __AK_FIXED_STRINGS__
#define __AK_FIXED_STRINGS__

#include "mStrings.h"
#include <Core/Memory/uniquePtrWrapper.h>

namespace Ak
{
    /**
     * fStrings are immutable strings. They are used for constants texts that don't need to be changed.
     * They are a wrapper around const char* string that provides methods like std::strings to get
     * informations about our string, and are compatible with mStrings.
     */
    class fString
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

            fString() : _string(nullptr) {}
            fString(const char* str);
            fString(const fString& str) : _string(str._string), _size(str._size) {}
            fString(fString&& str) : _string(str._string), _size(std::move(str)._size) {}

            fString(mString&& str);
            fString(mString&& str);

            fString(std::string& str);
            fString(std::string&& str);

            fString& operator=(const fString& str);
            fString& operator=(const char* str);

            inline fString& operator=(mString& str) { return operator=(str.c_str()); }
            inline fString& operator=(mString&& str) { return operator=(std::move(str).c_str()); }

            inline fString& operator=(std::string& str) { return operator=(str.c_str()); }
            inline fString& operator=(std::string&& str) { return operator=(std::move(str).c_str()); }

            inline size_t size() noexcept { return _size; }
            inline size_t length() noexcept { return _size; }
            inline bool empty() noexcept { return _string == nullptr || _string[0] == '\0' ? true : false; }

            // Getters
            inline const char& operator[](unsigned int index) const noexcept { return _string[index]; }
            inline const char& at(unsigned int index) const noexcept { return _string[index]; }
            inline const char back()  const noexcept { return _string[size() - 1]; }
            inline const char front() const noexcept { return _string[0]; }
            inline const char* data()  const noexcept { return &_string[0]; }
            inline const char* c_str() const noexcept { return &_string[0]; }

            // Finders
            size_t find(const char* str, size_t pos = 0);
            inline size_t find(fString&& str, size_t pos = 0) { return this->find(std::move(str).c_str(), pos); }
            inline size_t find(const fString& str, size_t pos = 0) { return this->find(str.c_str(), pos); }
            size_t find(char c, size_t pos = 0);

            size_t rfind(const char* str, size_t pos = npos);
            size_t rfind(fString&& str, size_t pos = npos);
            size_t rfind(const fString& str, size_t pos = npos);
            size_t rfind(char c, size_t pos = npos);

            inline friend std::ostream& operator<<(std::ostream& target, const fString& str) { return target << str.c_str(); }

            inline iterator begin() { return iterator(&_string[0]); }
            inline iterator end()   { return iterator(&_string[size()]); }

            inline bool operator==(const fString& str) noexcept { return std::strcmp(_string, str.c_str()) == 0; }
            inline bool operator!=(const fString& str) noexcept { return !*this == str; }

            ~fString() = default;

        private:
            static int compare(const char* p, const char* q, size_t n);
            
            const unique_ptr_w<char[]> _string;
            unsigned int _size = 0;
    };
}

#endif // __AK_FIXED_STRINGS__
