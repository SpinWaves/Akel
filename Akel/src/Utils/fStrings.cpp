// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/10/2021
// Updated : 06/05/2022

#include <Utils/fStrings.h>
#include <Core/core.h>

namespace Ak
{
    fString::fString(const char* str, size_t pos, size_t len, func::function<char(char)> modifier)
    {
        if(str == nullptr)
        {
            _string = nullptr;
            return;
        }

        char c = str[pos];
        while(c != '\0')
        {
            if(len != npos && _size == len)
                break;
            if(modifier != nullptr)
                _string[_size] = modifier(c);
            else
                _string[_size] = c;
            _size++;
            c = str[_size + pos];
        }
        _string[_size] = '\0';
    }

    fString::fString(const fString& str, size_t pos = 0, size_t len = npos, func::function<char(char)> modifier) : _size(len == npos ? str._size : len)
    {
        for(int i = 0; i < len == npos ? str._size : len; i++)
        {
            if(modifier != nullptr)
                _string[i] = modifier(str[i + pos]);
            else
                _string[i] = str[i + pos];
        }
    }
    fString::fString(fString&& str, size_t pos = 0, size_t len = npos, func::function<char(char)> modifier) : _size((len == npos ? str._size : len) 
    {
        for(int i = 0; i < len == npos ? str._size : len; i++)
        {
            if(modifier != nullptr)
                _string[i] = modifier(str[i + pos]);
            else
                _string[i] = str[i + pos];
        }
    }
    
    fString::fString(mString&& str, size_t pos, size_t len, func::function<char(char)> modifier) : _string(memAlloc<char>(len == npos ? str._size : len)), _size(len == npos ? str._size : len)
    {
        for(int i = 0; i < len == npos ? str._size : len; i++)
        {
            if(modifier != nullptr)
                _string[i] = modifier(str[i + pos]);
            else
                _string[i] = str[i + pos];
        }
    }
    
    fString::fString(mString&& str, size_t pos, size_t len, func::function<char(char) modifier) : _string(memAlloc<char>(len == npos ? str._size : len)), _size(len == npos ? str._size : len)
    {
        for(int i = 0; i < len == npos ? str._size : len; i++)
        {
            if(modifier != nullptr)
                _string[i] = modifier(str[i + pos]);
            else
                _string[i] = str[i + pos];
        }
    }

    fString::fString(std::string& str, size_t pos, size_t len, func::function<char(char) modifier) : _string(memAlloc<char>(len == npos ? str._size : len)), _size(len == npos ? str._size : len)
    {
        for(int i = 0; i < len == npos ? str._size : len; i++)
        {
            if(modifier != nullptr)
                _string[i] = modifier(str[i + pos]);
            else
                _string[i] = str[i + pos];
        }
    }
    fString::fString(std::string&& str, size_t pos, size_t len, func::function<char(char) modifier) : _string(memAlloc<char>(len == npos ? str._size : len)), _size(len == npos ? str._size : len)
    {
        for(int i = 0; i < len == npos ? str._size : len; i++)
        {
            if(modifier != nullptr)
                _string[i] = modifier(str[i + pos]);
            else
                _string[i] = str[i + pos];
        }
    }

    fString& fString::operator=(const fString& str)
    {
        if(_string != nullptr)
        {
            Core::log::report(ERROR, "fString: fStrings are constants strings that cannot be changed. To use operator \"=\" on a fString it needs to be empty");
            return *this;
        }
        _string = str.c_str();
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

        if(n == 0)
            return pos <= size ? pos : npos;
        if(pos >= size)
            return npos;

        const char& elem0 = str[0];
        const char* first = _string.get() + pos;
        const char* const last = _string.get() + _size;
        size_t len = _size - pos;

        while(len >= n)
        {
            first = static_cast<const char*>(std::memchr(first, elem0, len - n + 1));
            if(!first)
                return npos;
            if(compare(first, str, n) == 0)
                return first - _string.get();
            len = last - ++first;
        }
        return npos;
    }
    
    size_t fString::find(char c, size_t pos)
    {
        if(pos < _size)
        {
            const char* p = static_cast<const char*>(std::memchr(_string.get() + pos, c, _size - pos));
            if(p)
                return p - _string.get();
        }
        return npos;
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
        if(n <= _size)
        {
            pos = std::min(size_t(size_ - n), pos);
            do
            {
                if(compare(_string.get() + pos, str, n) == 0)
                    return pos;
            } while(pos-- > 0);
        }
        return npos;
    }
    
    size_t fString::rfind(char c, size_t pos)
    {
        size_t size = _size;
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
