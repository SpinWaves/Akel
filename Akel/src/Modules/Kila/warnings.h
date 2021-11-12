// This file is a part of Akel
// CREATED : 12/11/2021
// UPDATED : 12/11/2021

#ifndef __AK_KILA_WARNINGS__
#define __AK_KILA_WARNINGS__

#include <Core/core.h>

namespace Ak::Kl
{
    class Warning
    {
        public:
            Warning(const char* message, size_t line, size_t index);
            Warning(std::string message, size_t line, size_t index);

            inline const char* what() const noexcept { return _message.c_str(); }
            void expose() const noexcept;
            inline int line() const noexcept { return _line; }
            inline int index() const noexcept { return _index; }
        
        private:
            std::string _message;
            int _line = 0;
            int _index = 0;
    };

    Warning no_end(const char* message, size_t line , size_t index);
}

#endif // __AK_KILA_WARNINGS__
