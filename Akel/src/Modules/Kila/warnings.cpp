// This file is a part of Akel
// CREATED : 12/11/2021
// UPDATED : 12/11/2021

#include <Modules/Kila/warnings.h>

namespace Ak::Kl
{
    Warning::Warning(const char* message, size_t line, size_t index)
    {
        _message = message;
        _line = line + 1;
        _index = index;
    }
    Warning::Warning(std::string message, size_t line, size_t index)
    {
        _message = std::move(message);
        _line = line + 1;
        _index = index;
    }

    void Warning::expose() const
    {
        Core::log::report(WARNING, "%s, line: %d, index: %d", _message.c_str(), _line, _index);
    }

    Warning no_end(const char* message, size_t line , size_t index)
    {
        char dest[strlen(message) + 54];
        sprintf(dest, "Kila warning : expected closing %s, but none was found", message);
        return Warning(dest, line, index);
    }
}
