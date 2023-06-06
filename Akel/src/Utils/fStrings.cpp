// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/10/2021
// Updated : 05/06/2023

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

        _string = memAllocSize<char>(len == npos ? std::strlen(str) - pos + 1 : len - pos + 1);
		std::memset(_string, 0, len == npos ? std::strlen(str) - pos + 1 : len - pos + 1);

        char c;
        while((c = str[_size + pos]))
        {
            if(len != npos && _size == len)
                break;
            if(modifier != nullptr)
                _string[_size++] = modifier(c);
            else
                _string[_size++] = c;
        }
		_size++;
    }

    fString::fString(const fString& str, size_t pos, size_t len, func::function<char(char)> modifier) : _size(len == npos ? str._size - pos : len - pos)
    {
        _string = memAllocSize<char>(_size + 1);
        for(int i = 0; i < _size; i++)
        {
            if(modifier != nullptr)
                _string[i] = modifier(str[i + pos]);
            else
                _string[i] = str[i + pos];
        }
		_string[_size] = 0;
    }

    fString::fString(fString&& str, size_t pos, size_t len, func::function<char(char)> modifier) : _size(len == npos ? str._size - pos: len - pos)
    {
        _string = memAllocSize<char>(_size + 1);
        for(int i = 0; i <= _size; i++)
        {
            if(modifier != nullptr)
                _string[i] = modifier(str[i + pos]);
            else
                _string[i] = str[i + pos];
        }
		_string[_size] = 0;
    }
    
    fString::fString(mString& str, size_t pos, size_t len, func::function<char(char)> modifier) : _size(len == npos ? str.size() - pos : len - pos)
    {
        _string = memAllocSize<char>(_size + 1);
        for(int i = 0; i < _size; i++)
        {
            if(modifier != nullptr)
                _string[i] = modifier(str[i + pos]);
            else
                _string[i] = str[i + pos];
        }
		_string[_size] = 0;
    }
    
    fString::fString(mString&& str, size_t pos, size_t len, func::function<char(char)> modifier) : _size(len == npos ? str.size() - pos : len - pos)
    {
        _string = memAllocSize<char>(_size + 1);
        for(int i = 0; i < _size; i++)
        {
            if(modifier != nullptr)
                _string[i] = modifier(str[i + pos]);
            else
                _string[i] = str[i + pos];
        }
		_string[_size] = 0;
    }

    fString::fString(std::string& str, size_t pos, size_t len, func::function<char(char)> modifier) : _size(len == npos ? str.size() - pos : len - pos)
    {
        _string = memAllocSize<char>(_size + 1);
        for(int i = 0; i < _size; i++)
        {
            if(modifier != nullptr)
                _string[i] = modifier(str[i + pos]);
            else
                _string[i] = str[i + pos];
        }
		_string[_size] = 0;
    }

    fString::fString(std::string&& str, size_t pos, size_t len, func::function<char(char)> modifier) : _size(len == npos ? str.size() - pos : len - pos)
    {
        _string = memAllocSize<char>(_size + 1);
        for(int i = 0; i < _size; i++)
        {
            if(modifier != nullptr)
                _string[i] = modifier(str[i + pos]);
            else
                _string[i] = str[i + pos];
        }
		_string[_size] = 0;
    }

    fString& fString::operator=(const fString& str)
    {
        if(_string != nullptr)
        {
            Core::log::report(ERROR, "fString: fStrings are constants strings that cannot be changed. To use operator \"=\" on a fString it needs to be empty");
            return *this;
        }
        _string = memAllocSize<char>(str._size);
        std::memcpy((void*)_string, (void*)str._string, str._size);
        return *this;
    }

    fString& fString::operator=(const char* str)
    {
        if(_string != nullptr)
        {
            Core::log::report(ERROR, "fString: fStrings are constants strings that cannot be changed. To use operator \"=\" on a fString it needs to be empty");
            return *this;
        }
        size_t size = std::strlen(str);
        _string = memAllocSize<char>(size + 1);
        std::memcpy((void*)_string, (void*)str, size);
		_string[size] = 0;
        return *this;
    }
    
    size_t fString::find(const char* str, size_t pos)
    {
        const size_t n = (size_t)std::strlen(str);

        if(n == 0)
            return pos <= _size ? pos : npos;
        if(pos >= _size)
            return npos;

        const char& elem0 = str[0];
        const char* first = _string + pos;
        const char* const last = _string + _size;
        size_t len = _size - pos;

        while(len >= n)
        {
            first = static_cast<const char*>(std::memchr(first, elem0, len - n + 1));
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
        if(pos < _size)
        {
            const char* p = static_cast<const char*>(std::memchr(_string + pos, c, _size - pos));
            if(p)
                return p - _string;
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
            pos = std::min(size_t(_size - n), pos);
            do
            {
                if(compare(_string + pos, str, n) == 0)
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

    fString::~fString()
    {
        memFree(_string);
    }
}
