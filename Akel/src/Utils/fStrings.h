// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/10/2021
// Updated : 21/08/2022

#ifndef __AK_FIXED_STRINGS__
#define __AK_FIXED_STRINGS__

#include "mStrings.h"

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
            fString(const char* str, size_t pos = 0, size_t len = npos, func::function<char(char)> modifier = nullptr);

            fString(const fString& str, size_t pos = 0, size_t len = npos, func::function<char(char)> modifier = nullptr);
            fString(fString&& str, size_t pos = 0, size_t len = npos, func::function<char(char)> modifier = nullptr);

            fString(mString& str, size_t pos = 0, size_t len = npos, func::function<char(char)> modifier = nullptr);
            fString(mString&& str, size_t pos = 0, size_t len = npos, func::function<char(char)> modifier = nullptr);

            fString(std::string& str, size_t pos = 0, size_t len = npos, func::function<char(char)> modifier = nullptr);
            fString(std::string&& str, size_t pos = 0, size_t len = npos, func::function<char(char)> modifier = nullptr);

            fString& operator=(const fString& str);
            fString& operator=(const char* str);

            inline fString& operator=(mString& str) { return operator=(str.c_str()); }
            inline fString& operator=(mString&& str) { return operator=(std::move(str).c_str()); }

            inline fString& operator=(std::string& str) { return operator=(str.c_str()); }
            inline fString& operator=(std::string&& str) { return operator=(std::move(str).c_str()); }

            inline size_t size() noexcept { return _size; }
            inline size_t length() noexcept { return _size; }
            inline bool empty() noexcept { return _string == nullptr || _string[0] == '\0'; }

            // Getters
            inline char operator[](unsigned int index) const noexcept { return _string[index]; }
            inline char at(unsigned int index) const noexcept { return _string[index]; }
            inline char back()  const noexcept { return _string[_size - 1]; }
            inline char front() const noexcept { return _string[0]; }
            inline const char* data()  const noexcept { return _string; }
            inline const char* c_str() const noexcept { return _string; }

            // Finders
            size_t find(const char* str, size_t pos = 0);
            inline size_t find(fString&& str, size_t pos = 0) { return this->find(std::move(str).c_str(), pos); }
            inline size_t find(const fString& str, size_t pos = 0) { return this->find(str.c_str(), pos); }
            size_t find(char c, size_t pos = 0);

            size_t rfind(const char* str, size_t pos = npos);
            size_t rfind(fString&& str, size_t pos) { return this->rfind(std::move(str).c_str(), pos); }
            size_t rfind(const fString& str, size_t pos) { return this->rfind(str.c_str(), pos); }
            size_t rfind(char c, size_t pos = npos);

			inline friend std::ostream& operator<<(std::ostream& target, const fString& str) { return target << str._string; }

            inline iterator begin() { return iterator(&_string[0]); }
            inline iterator end()   { return iterator(&_string[_size]); }

            inline bool operator==(fString str) noexcept { return std::strcmp(_string, std::move(str).c_str()) == 0; }
            inline bool operator!=(fString str) noexcept { return !operator==(std::move(str)); }
            inline bool operator==(std::string& str) noexcept { return std::strcmp(_string, str.c_str()) == 0; }
            inline bool operator!=(std::string& str) noexcept { return !operator==(str); }
            inline bool operator==(mString str) noexcept { return std::strcmp(_string, std::move(str).c_str()) == 0; }
            inline bool operator!=(mString str) noexcept { return !operator==(std::move(str)); }
            inline bool operator==(const char* str) noexcept { return std::strcmp(_string, str) == 0; }
            inline bool operator!=(const char* str) noexcept { return !operator==(str); }

            inline bool operator>(fString str) noexcept { return std::strcmp(_string, std::move(str).c_str()) > 0; }
            inline bool operator<(fString str) noexcept { return std::strcmp(_string, std::move(str).c_str()) < 0; }
            inline bool operator>(std::string& str) noexcept { return std::strcmp(_string, str.c_str()) > 0; }
            inline bool operator<(std::string& str) noexcept { return std::strcmp(_string, str.c_str()) < 0; }
            inline bool operator>(mString str) noexcept { return std::strcmp(_string, std::move(str).c_str()) > 0; }
            inline bool operator<(mString str) noexcept { return std::strcmp(_string, std::move(str).c_str()) < 0; }
            inline bool operator>(const char* str) noexcept { return std::strcmp(_string, str) > 0; }
            inline bool operator<(const char* str) noexcept { return std::strcmp(_string, str) < 0; }

            inline bool operator>=(fString str) noexcept { return std::strcmp(_string, std::move(str).c_str()) > -1; }
            inline bool operator<=(fString str) noexcept { return std::strcmp(_string, std::move(str).c_str()) < 1; }
            inline bool operator>=(std::string& str) noexcept { return std::strcmp(_string, str.c_str()) > -1; }
            inline bool operator<=(std::string& str) noexcept { return std::strcmp(_string, str.c_str()) < 1; }
            inline bool operator>=(mString str) noexcept { return std::strcmp(_string, std::move(str).c_str()) > -1; }
            inline bool operator<=(mString str) noexcept { return std::strcmp(_string, std::move(str).c_str()) < 1; }
            inline bool operator>=(const char* str) noexcept { return std::strcmp(_string, str) > -1; }
            inline bool operator<=(const char* str) noexcept { return std::strcmp(_string, str) < 1; }

            ~fString();

        private:
            static int compare(const char* p, const char* q, size_t n);
            
            char* _string;
            size_t _size = 0;
    };
}

#endif // __AK_FIXED_STRINGS__
