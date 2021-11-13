// This file is a part of Akel
// CREATED : 12/11/2021
// UPDATED : 13/11/2021

#ifndef __AK_KILA_WARNINGS__
#define __AK_KILA_WARNINGS__

#include <Core/core.h>

namespace Ak::Kl
{
    class Warning
    {
        public:
            Warning(const char* message, size_t line);
            Warning(std::string message, size_t line);

            inline const char* what() const noexcept { return _message.c_str(); }
            void expose() const;
            inline int line() const noexcept { return _line; }
        
        private:
            std::string _message;
            int _line = 0;
    };

    Warning no_end(const char* message, size_t line);
}

#endif // __AK_KILA_WARNINGS__
