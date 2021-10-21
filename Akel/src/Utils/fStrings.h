// This file is a part of Akel
// CREATED : 21/10/2021
// UPDATED : 21/10/2021

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
            explicit fString() = default;
            explicit fString(const char* str);
            explicit fString(const fString& str); // A constructor cannot accept a object passed by value
            explicit fString(fString&& str);

            fString& operator=(fString str);
            fString& operator=(const char* str);

            size_t size()       { return sizeof(_string); }
            size_t length()     { return sizeof(_string); }
            bool empty() const  { return sizeof(_string) == 0; }

            // Getters
            char operator[](unsigned int index);
            char at(unsigned int index);
            char* back();
            char front();
            const char* c_str() { return _string; }

            // Finders
            int find(fString str);
            int rfind(fString str);

            ~fString() = default;

            inline static const size_t npos = -1;

        private:
            const char* _string = nullptr;
    };
}

#endif // __AK_FIXED_STRINGS__
