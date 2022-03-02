// This file is a part of Akel
// Author : @kbz_8
// CREATED : 21/10/2021
// UPDATED : 11/12/2021

#include <Utils/fStrings.h>
#include <Core/core.h>

namespace Ak
{
    fString::fString(const char* str)
    {
        _string = str;
    }
    fString::fString(const fString& str)
    {
        _string = str.c_str();
    }
    fString::fString(fString&& str)
    {
        _string = std::move(str).c_str();
    }

    fString& fString::operator=(const fString& str)
    {
        if(_string != nullptr)
        {
            Core::log::report(ERROR, "fString: fStrings are constants strings that cannot be changed. To use operator \"=\" on a fString it needs to be empty");
            return *this;
        }
        _string = std::move(str).c_str();
        return *this;
    }
    fString& fString::operator=(const char* str)
    {
        if(_string != nullptr)
        {
            Core::log::report(ERROR, "fString: fStrings are constants strings that cannot be changed. To use operator \"=\" on a fString it needs to be empty");
            return *this;
        }
        _string = str;
        return *this;
    }

    size_t fString::size() noexcept
    {
        int Size = 0;
        while(_string[Size] != '\0') Size++;
        return Size;
    }
    size_t fString::length() noexcept
    {
        int Size = 0;
        while(_string[Size] != '\0') Size++;
        return Size;
    }
    
    size_t fString::find(const char* str, size_t pos)
    {
        const size_t n = (size_t)std::strlen(str);
        const size_t size = this->size();

        if(n == 0)
            return pos <= size ? pos : npos;
        if(pos >= size)
            return npos;

        const char& elem0 = str[0];
        const char* first = _string + pos;
        const char* const last = _string + size;
        size_t len = size - pos;

        while(len >= n)
        {
            first = static_cast<const char*>(memchr(first, elem0, len - n + 1));
            if(!first)
                return npos;
            if(compare(first, str, n) == 0)
                return first - _string;
            len = last - ++first;
        }
        return npos;
    }
    size_t fString::find(fString&& str, size_t pos)
    {
        return this->find(std::move(str).c_str(), pos);
    }
    size_t fString::find(const fString& str, size_t pos)
    {
        return this->find(str.c_str(), pos);
    }
    size_t fString::find(char c, size_t pos)
    {
        size_t ret = npos;
        const size_t size = this->size();
        if(pos < size)
        {
            const size_t n = size - pos;
            const char* p = static_cast<const char*>(memchr(_string + pos, c, n));
            if(p)
                ret = p - _string;
        }
        return ret;
    }
    int fString::compare(const char* p, const char* q, size_t n)
    {
        while(n--)
        {
            if(!std::tolower(*p) == std::tolower(*q))
                return *p < *q ? -1 : 1;
            p++; q++;
        }
        return 0;
    }
    size_t fString::rfind(const char* str, size_t pos)
    {   
        const size_t n = (size_t)std::strlen(str);
        const size_t size = this->size();
        if(n <= size)
        {
            pos = std::min(size_t(size - n), pos);
            do
            {
                if(compare(_string + pos, str, n) == 0)
                    return pos;
            } while(pos-- > 0);
        }
        return npos;
    }
    size_t fString::rfind(fString&& str, size_t pos)
    {
        return this->rfind(std::move(str).c_str(), pos);
    }
    size_t fString::rfind(const fString& str, size_t pos)
    {
        return this->rfind(str.c_str(), pos);
    }
    size_t fString::rfind(char c, size_t pos)
    {
        size_t size = this->size();
        if(size)
        {
            if(size-- > pos)
                size = pos;
            for(size++; size-- > 0;)
                if(std::tolower(_string[size]) == std::tolower(c))
                    return size;
        }
        return npos;
    }
}
