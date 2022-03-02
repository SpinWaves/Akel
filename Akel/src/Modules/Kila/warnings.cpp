// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/11/2021
// Updated : 25/02/2022

#include <Modules/Kila/warnings.h>

namespace Ak::Kl
{
    Warning::Warning(const char* message, size_t line)
    {
        _message = message;
        _line = line + 1;
    }
    Warning::Warning(std::string message, size_t line)
    {
        _message = std::move(message);
        _line = line + 1;
    }

    Warning no_end(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 54, '\0');
        sprintf(&dest[0], "Kila warning : expected closing %s, but none was found", message);
        return Warning(std::move(dest), line);
    }
}
