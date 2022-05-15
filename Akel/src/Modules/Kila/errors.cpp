// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/11/2021
// Updated : 15/05/2022

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
            Core::log::report(FATAL_ERROR, "[Kila Error] : %s", _message.c_str());
        else
            Core::log::report(FATAL_ERROR, "[Kila Error] : %s, at line: %d", _message.c_str(), _line);
    }

    Error parsing_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 32, '\0');
        sprintf(&dest[0], "parsing error : '%s'", message);
        return Error(std::move(dest), line);
    }
    Error syntax_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 31, '\0');
        sprintf(&dest[0], "syntax error : '%s'", message);
        return Error(std::move(dest), line);
    }
    Error semantic_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 33, '\0');
        sprintf(&dest[0], "semantic error : %s", message);
        return Error(std::move(dest), line);
    }
    Error compiler_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 33, '\0');
        sprintf(&dest[0], "compiler error : %s", message);
        return Error(std::move(dest), line);
    }

    Error unexpected_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 43, '\0');
        sprintf(&dest[0], "parsing error : unexpected '%s'", message);
        return Error(std::move(dest), line);
    }
    Error unexpected_syntax_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 42, '\0');
        sprintf(&dest[0], "unexpected syntax : '%s'", message);
        return Error(std::move(dest), line);
    }
    Error unexpected_macro_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 38, '\0');
        sprintf(&dest[0], "parsing error : unexpected '%s' as macro", message);
        return Error(std::move(dest), line);
    }
    Error expected_syntax_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 40, '\0');
        sprintf(&dest[0], "expected syntax : '%s'", message);
        return Error(std::move(dest), line);
    }
    Error undeclared_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 35, '\0');
        sprintf(&dest[0], "undeclared : '%s'", message);
        return Error(std::move(dest), line);
    }
    Error wrong_type_error(const char* message, const char* destination, bool lvalue, size_t line)
    {
        std::string dest = "wrong type : ";
        if(lvalue)
        {
            dest += "'";
            dest += message;
            dest += "' is not a lvalue";
        }
        else
        {
            dest += "cannot convert '";
            dest +=  message;
            dest += "' to '";
            dest +=  destination;
            dest += "'";
        }
        return Error(std::move(dest), line);
    }
    Error already_declared_error(const char* message, size_t line)
    {
        std::string dest(strlen(message) + 41, '\0');
        sprintf(&dest[0], "already declared : '%s'", message);
        return Error(std::move(dest), line);
    }

    Error file_not_found(const char* file)
    {
        std::string msg = "file not found : ";
        msg += file;
        return Error(std::move(msg), -2);
    }
}
