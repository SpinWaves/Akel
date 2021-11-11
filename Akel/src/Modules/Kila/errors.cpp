// This file is a part of Akel
// CREATED : 11/11/2021
// UPDATED : 11/11/2021

#include <Modules/Kila/errors.h>

namespace Ak::Kl
{
    Error::Error(const char* message, size_t line, size_t index)
    {
        _message = message;
        _line = line + 1;
        _index = index;
    }
    Error::Error(std::string message, size_t line, size_t index)
    {
        _message = std::move(message);
        _line = line + 1;
        _index = index;
    }

    void Error::expose() const noexcept
    {
        if(_line == -1 && _index == -1)
            Core::log::report(FATAL_ERROR, _message);
        else
            Core::log::report(FATAL_ERROR, "%s, line: %d, index: %d",_message.c_str() , _line, _index);
    }

    Error parsing_error(const char* message, size_t line, size_t index)
    {
        char dest[strlen(message) + 29];
        strcat(dest, "Kila error : parsing error : ");
        strcat(dest, message);
        return Error(dest, line, index);
    }
    Error syntax_error(const char* message, size_t line, size_t index)
    {
        char dest[strlen(message) + 28];
        strcat(dest, "Kila error : syntax error : ");
        strcat(dest, message);
        return Error(dest, line, index);
    }
    Error semantic_error(const char* message, size_t line, size_t index)
    {
        char dest[strlen(message) + 30];
        strcat(dest, "Kila error : semantic error : ");
        strcat(dest, message);
        return Error(dest, line, index);
    }
    Error compiler_error(const char* message, size_t line, size_t index)
    {
        char dest[strlen(message) + 30];
        strcat(dest, "Kila error : compiler error : ");
        strcat(dest, message);
        return Error(dest, line, index);
    }

    Error unexpected_error(const char* message, size_t line, size_t index)
    {
        char dest[strlen(message) + 42];
        strcat(dest, "Kila error : parsing error : unexpected '");
        strcat(dest, message);
        strcat(dest, "'");
        return Error(dest, line, index);
    }
    Error unexpected_syntax_error(const char* message, size_t line, size_t index)
    {
        char dest[strlen(message) + 39];
        strcat(dest, "Kila error : unexpected syntax error : ");
        strcat(dest, message);
        return Error(dest, line, index);
    }
    Error expected_syntax_error(const char* message, size_t line, size_t index)
    {
        char dest[strlen(message) + 37];
        strcat(dest, "Kila error : expected syntax error : ");
        strcat(dest, message);
        return Error(dest, line, index);
    }
    Error undeclared_error(const char* message, size_t line, size_t index)
    {
        char dest[strlen(message) + 32];
        strcat(dest, "Kila error : undeclared error : ");
        strcat(dest, message);
        return Error(dest, line, index);
    }
    Error wrong_type_error(const char* message, const char* destination, bool lvalue, size_t line, size_t index)
    {
        char dest[strlen(message) + 32];
        strcat(dest, "Kila error : wrong type error : ");
        strcat(dest, message);
        return Error(dest, line, index);
    }
    Error already_declared_error(const char* message, size_t line, size_t index)
    {
        char dest[strlen(message) + 38];
        strcat(dest, "Kila error : already declared error : ");
        strcat(dest, message);
        return Error(dest, line, index);
    }

    Error file_not_found(const char* file)
    {
        std::string msg = "Kila error : file not found : ";
        msg += file;
        return Error(msg, -1, -1);
    }
}
