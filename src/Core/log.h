// This file is a part of AtlasEngine
// CREATED : 03/04/2021
// UPDATED : 25/04/2021

#ifndef __LOG__
#define __LOG__

#include <AEpch.h>

enum LogType
{
    MESSAGE,
    WARNING,
    ERROR,
    FATAL_ERROR
};

namespace AE::Core
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

#endif // __LOG__
