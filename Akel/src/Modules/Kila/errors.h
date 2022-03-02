// This file is a part of Akel
// Author : @kbz_8
// CREATED : 11/11/2021
// UPDATED : 13/11/2021

#ifndef __AK_KILA_ERRORS__
#define __AK_KILA_ERRORS__

#include <Core/core.h>

namespace Ak::Kl
{
    class Error
    {
        public:
            Error(const char* message, size_t line);
            Error(std::string message, size_t line);

            inline const char* what() const noexcept { return _message.c_str(); }
            void expose() const;
            inline int line() const noexcept { return _line; }
        
        private:
            std::string _message;
            int _line = 0;
    };

    Error parsing_error(const char* message, size_t line);
	Error syntax_error(const char* message, size_t line);
	Error semantic_error(const char* message, size_t line);
	Error compiler_error(const char* message, size_t line);

	Error unexpected_error(const char* unexpected, size_t line);
	Error unexpected_macro_error(const char* unexpected, size_t line);
	Error unexpected_syntax_error(const char* unexpected, size_t line);
	Error expected_syntax_error(const char* expected, size_t line);
	Error undeclared_error(const char* undeclared, size_t line);
	Error wrong_type_error(const char* source, const char* destination, bool lvalue, size_t line);
	Error already_declared_error(const char* name, size_t line);

    Error file_not_found(const char* file);
}

#endif // __AK_KILA_ERRORS__
