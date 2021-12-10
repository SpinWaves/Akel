// This file is a part of Akel
// CREATED : 21/10/2021
// UPDATED : 09/12/2021

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

    fString& fString::operator=(fString str)
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

    char fString::operator[](unsigned int index)
    {
        return _string[index];
    }
    char fString::at(unsigned int index)
    {
        return _string[index];
    }
    char fString::back()
    {
        return _string[sizeof(_string) - 1];
    }
    char fString::front()
    {
        return _string[0];
    }

    size_t fString::find(fString str)
    {
        
    }
    size_t fString::rfind(fString str)
    {
        // TODO
    }
}
