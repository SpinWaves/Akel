// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/11/2021
// Updated : 13/05/2022

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
        std::string dest(strlen(message) + 29, '\0');
        sprintf(&dest[0], "Kila error : parsing error : %s", message);
        return Error(std::move(dest), line);
    }
    Error syntax_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 28, '\0');
        sprintf(&dest[0], "Kila error : syntax error : %s", message);
        return Error(std::move(dest), line);
    }
    Error semantic_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 30, '\0');
        sprintf(&dest[0], "Kila error : semantic error : %s", message);
        return Error(std::move(dest), line);
    }
    Error compiler_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 30, '\0');
        sprintf(&dest[0], "Kila error : compiler error : %s", message);
        return Error(std::move(dest), line);
    }

    Error unexpected_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 42, '\0');
        sprintf(&dest[0], "Kila error : parsing error : unexpected '%s'", message);
        return Error(std::move(dest), line);
    }
    Error unexpected_syntax_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 39, '\0');
        sprintf(&dest[0], "Kila error : unexpected syntax error : %s", message);
        return Error(std::move(dest), line);
    }
    Error expected_syntax_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 37, '\0');
        sprintf(&dest[0], "Kila error : expected syntax error : %s", message);
        return Error(std::move(dest), line);
    }
    Error undeclared_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 32, '\0');
        sprintf(&dest[0], "Kila error : undeclared error : %s", message);
        return Error(std::move(dest), line);
    }
    Error wrong_type_error(const char* message, const char* destination, bool lvalue, size_t line)
    {
        std::string dest = "Kila error : wrong type : '";
        if(lvalue)
            dest += message;
        else
        {
            dest += "cannot convert '";
            dest += message;
            dest += "' to '";
            dest += destination;
        }
        dest += '\'';
        return Error(std::move(dest), libe);
    }
    Error already_declared_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 38, '\0');
        sprintf(&dest[0], "Kila error : already declared error : %s", message);
        return Error(std::move(dest), line);
    }

    Error file_not_found(const char* file)
    {
        std::string msg = "Kila error : file not found : ";
        msg += file;
        return Error(std::move(msg), -1);
    }
}
