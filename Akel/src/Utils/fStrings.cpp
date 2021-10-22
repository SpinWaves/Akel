// This file is a part of Akel
// CREATED : 21/10/2021
// UPDATED : 21/10/2021

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

    int fString::find(fString str)
    {
        // TODO
    }
    int fString::rfind(fString str)
    {
        // TODO
    }
}
