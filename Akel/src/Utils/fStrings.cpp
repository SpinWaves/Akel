// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/10/2021
// Updated : 29/04/2022

#include <Utils/fStrings.h>
#include <Core/core.h>

namespace Ak
{
    fString::fString(const char* str)
    {
        if(str == nullptr)
        {
            _string = nullptr;
            return;
        }

        char c = str[0];
        while(c != '\0')
        {
            _string[_size] = str[_size];
            _size++;
            c = str[_size];
        }
        _string[_size] = '\0';
    }
    
    fString::fString(mString&& str) : _string(memAlloc<char>(str.size())), _size(str.size())
    {
        for(int i = 0; i < str.size(); i++)
            _string[i] = str[i];
    }
    fString::fString(mString&& str) : _string(memAlloc<char>(str.size())), _size(str.size())
    {
        for(int i = 0; i < str.size(); i++)
            _string[i] = str[i];
    }

    fString::fString(std::string& str) : _string(memAlloc<char>(str.size())), _size(str.size())
    {
        for(int i = 0; i < str.size(); i++)
            _string[i] = str[i];
    }
    fString::fString(std::string&& str) : _string(memAlloc<char>(str.size())), _size(str.size())
    {
        for(int i = 0; i < str.size(); i++)
            _string[i] = str[i];
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
