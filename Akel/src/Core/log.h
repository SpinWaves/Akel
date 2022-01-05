// This file is a part of Akel
// CREATED : 03/04/2021
// UPDATED : 05/01/2022

#ifndef __AK_LOG__
#define __AK_LOG__

#include <Akpch.h>
#include <Utils/utils.h>

enum LogType
{
    MESSAGE,
    WARNING,
    ERROR,
    FATAL_ERROR
};

namespace Ak
{
    namespace Core
    {
        class log
        {
            public:
                explicit log() = delete;
                static void Init();
                static void report(enum LogType type, std::string message, ...);
                static void report(std::string message, ...);
                ~log() = delete;

            private:
                static std::string getTime(const std::string& path);
                static void TERMINATE() noexcept;
                inline static std::ofstream _out;
                inline static std::string _type;
                inline static MutexHandel mutex;
        };
    }

    void FatalError(std::string message, ...);
    void Error(std::string message, ...);
    void Warning(std::string message, ...);
    void Message(std::string message, ...);
}

#define AK_BEGIN_SESSION(name) Ak::Core::log::report("Begin " name " ----")
#define AK_END_SESSION() Ak::Core::log::report("End ----")

#endif // __AK_LOG__
