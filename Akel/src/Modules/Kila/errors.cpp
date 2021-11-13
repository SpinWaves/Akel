// This file is a part of Akel
// CREATED : 11/11/2021
// UPDATED : 13/11/2021

#include <Modules/Kila/errors.h>

namespace Ak::Kl
{
    Error::Error(const char* message, size_t line)
    {
        _message = message;
        _line = line + 1;
    }
    Error::Error(std::string message, size_t line)
    {
        _message = std::move(message);
        _line = line + 1;
    }

    void Error::expose() const
    {
        if(_line == -1)
            Core::log::report(FATAL_ERROR, _message);
        else
            Core::log::report(FATAL_ERROR, "%s, line: %d", _message.c_str(), _line);
    }

    Error parsing_error(const char* message, size_t line)
    {
        char dest[strlen(message) + 29];
        sprintf(dest, "Kila error : parsing error : %s", message);
        return Error(dest, line);
    }
    Error syntax_error(const char* message, size_t line)
    {
        char dest[strlen(message) + 28];
        sprintf(dest, "Kila error : syntax error : %s", message);
        return Error(dest, line);
    }
    Error semantic_error(const char* message, size_t line)
    {
        char dest[strlen(message) + 30];
        sprintf(dest, "Kila error : semantic error : %s", message);
        return Error(dest, line);
    }
    Error compiler_error(const char* message, size_t line)
    {
        char dest[strlen(message) + 30];
        sprintf(dest, "Kila error : compiler error : %s", message);
        return Error(dest, line);
    }

    Error unexpected_error(const char* message, size_t line)
    {
        char dest[strlen(message) + 42];
        sprintf(dest, "Kila error : parsing error : unexpected '%s'", message);
        return Error(dest, line);
    }
	Error unexpected_macro_error(const char* message, size_t line)
    {
        char dest[strlen(message) + 51];
        sprintf(dest, "Kila error : parsing error : unexpected '%s' as macro", message);
        return Error(dest, line);
    }
    Error unexpected_syntax_error(const char* message, size_t line)
    {
        char dest[strlen(message) + 39];
        sprintf(dest, "Kila error : unexpected syntax error : %s", message);
        return Error(dest, line);
    }
    Error expected_syntax_error(const char* message, size_t line)
    {
        char dest[strlen(message) + 37];
        sprintf(dest, "Kila error : expected syntax error : %s", message);
        return Error(dest, line);
    }
    Error undeclared_error(const char* message, size_t line)
    {
        char dest[strlen(message) + 32];
        sprintf(dest, "Kila error : undeclared error : %s", message);
        return Error(dest, line);
    }
    Error wrong_type_error(const char* message, const char* destination, bool lvalue, size_t line)
    {
        char dest[strlen(message) + 32];
        sprintf(dest, "Kila error : wrong type error : %s", message);
        return Error(dest, line);
    }
    Error already_declared_error(const char* message, size_t line)
    {
        char dest[strlen(message) + 38];
        sprintf(dest, "Kila error : already declared error : %s", message);
        return Error(dest, line);
    }

    Error file_not_found(const char* file)
    {
        std::string msg = "Kila error : file not found : ";
        msg += file;
        return Error(std::move(msg), -1);
    }
}
