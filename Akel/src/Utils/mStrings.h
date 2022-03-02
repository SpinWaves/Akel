// This file is a part of Akel
// Author : @kbz_8
// CREATED : 10/10/2021
// UPDATED : 11/12/2021

#ifndef __AK_MUTABLE_STRINGS__
#define __AK_MUTABLE_STRINGS__

#include <Akpch.h>

namespace Ak
{
    class mString
    {
        public:
            inline static const size_t npos = -1;
            /**
             * mStrings are transmitted by value and not by copy and 
             * rvalue reference because the costs are either the same or higher
             * copy lvalue: 5e-06 sec
             * move rvalue: 1e-06 sec
             * by value (passing a lvalue): 2e-06 sec
             * by value (passing a rvalue): 1e-06 sec
             */
            explicit mString();
            explicit mString(const char* str);
            explicit mString(const mString& str); // A constructor cannot accept a object passed by value
            explicit mString(mString&& str);

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


            ~mString() = default;

        private:
            std::vector<char> _string;
    };
}

#endif // __AK_MUTABLE_STRINGS__
