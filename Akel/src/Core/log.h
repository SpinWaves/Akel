// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2021
// Updated : 11/08/2022

#ifndef __AK_LOG__
#define __AK_LOG__

#include <Akpch.h>
#include <Utils/utils.h>

enum LogType
{
    MESSAGE,
    WARNING,
    STRONG_WARNING,
    ERROR,
    FATAL_ERROR
};

namespace Ak
{
    namespace Core
    {
        class log
        {
			friend class Paths;
            public:
                log() = delete;
                static void Init(std::string path);
                static void report(enum LogType type, std::string message, ...);
                static void report(std::string message, ...);
                ~log() = delete;

            private:
				inline static const std::string& getLogPath() { return _log_dir; };
                static std::string getTime();
                inline static std::ofstream _out;
                inline static std::string _type;
                inline static std::mutex mutex;
				inline static std::string _log_dir;
        };
    }

    void FatalError(std::string message, ...);
    void Error(std::string message, ...);
    void Warning(std::string message, ...);
    void Strong_Warning(std::string message, ...);
    void Message(std::string message, ...);
}

#define AK_BEGIN_SESSION(name) Ak::Core::log::report("Begin " name " ----")
#define AK_END_SESSION() Ak::Core::log::report("End ----")

#endif // __AK_LOG__
