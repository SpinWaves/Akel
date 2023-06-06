// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2021
// Updated : 07/06/2023

#ifndef __AK_LOG__
#define __AK_LOG__

#include <Akpch.h>
#include <Utils/utils.h>
#include <Core/profile.h>

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
	class VFS;

    namespace Core
    {
        class AK_API log
        {
			friend class Ak::VFS;
            public:
                log() = delete;
                static void init(std::filesystem::path path);
                static void report(enum LogType type, std::string message, ...);
                static void report(std::string message, ...);
                ~log() = delete;

            private:
				inline static const std::filesystem::path& getLogPath() { return _log_dir; };
                static std::string getTime();

			private:
                inline static std::mutex mutex;
				inline static std::filesystem::path _log_dir;
                inline static std::ofstream _out;
                inline static std::string _type;
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
