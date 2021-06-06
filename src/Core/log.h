// This file is a part of Akel
// CREATED : 03/04/2021
// UPDATED : 03/06/2021

#ifndef __AK_LOG__
#define __AK_LOG__

#include <Akpch.h>

enum LogType
{
    MESSAGE,
    WARNING,
    ERROR,
    FATAL_ERROR
};

namespace Ak::Core
{
    class log
    {
        public:
            static void report(enum LogType type, std::string message, std::string path);

        private:
            static std::string getTime(enum LogType type, std::string path);
            static void TERMINATE();
    };
}

#endif // __AK_LOG__
