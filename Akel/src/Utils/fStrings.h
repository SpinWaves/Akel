// This file is a part of Akel
// CREATED : 21/10/2021
// UPDATED : 10/12/2021

#ifndef __AK_FIXED_STRINGS__
#define __AK_FIXED_STRINGS__

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

            explicit fString() = default;
            explicit fString(const char* str);
            explicit fString(const fString& str); // A constructor cannot accept a object passed by value
            explicit fString(fString&& str);

            fString& operator=(fString str);
            fString& operator=(const char* str);

            size_t size() noexcept;
            size_t length() noexcept;
            inline bool empty() noexcept { return size() == 0; }

            // Getters
            char operator[](unsigned int index);
            char at(unsigned int index);
            char back();
            char front();
            inline const char* c_str() const noexcept { return _string; }

            // Finders
            size_t find(fString str);
            size_t rfind(fString str);

            friend std::ostream& operator<<(std::ostream& target, const fString& str) { return target << str.c_str(); }

            inline iterator begin() { return iterator(&_string[0]); }
            inline iterator end()   { return iterator(&_string[size()]); } 

            ~fString() = default;

            inline static const size_t npos = -1;

        private:
            const char* _string = nullptr;
    };
}

#endif // __AK_FIXED_STRINGS__
