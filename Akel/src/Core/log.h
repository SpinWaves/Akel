// This file is a part of Akel
// CREATED : 03/04/2021
// UPDATED : 13/09/2021

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
            log() = delete;
			static void Init();
            static void report(enum LogType type, std::string message, ...);
            static void report(std::string message, ...);
            ~log() = delete;

        private:
            static std::string getTime(std::string path);
            static void TERMINATE();
			inline static std::ofstream _out;
			inline static std::string _type;
    };
}

#define AK_BEGIN_SESSION(name) Ak::Core::log::report("Begin " name " ----")
#define AK_END_SESSION() Ak::Core::log::report("End ----")

#endif // __AK_LOG__
