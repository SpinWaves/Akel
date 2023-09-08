// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2021
// Updated : 08/09/2023

#ifndef __AK_LOG__
#define __AK_LOG__

#include <Akpch.h>
#include <Utils/utils.h>
#include <Core/profile.h>

enum LogType
{
	DEBUGLOG,
    MESSAGE,
    WARNING,
    STRONG_WARNING,
    ERROR,
    FATAL_ERROR
};

namespace Ak
{
    namespace Core::log
    {
		void AK_API report(enum LogType type, std::string message, ...);
		void AK_API report(std::string message, ...);
    }

    void AK_API FatalError(std::string message, ...);
    void AK_API Error(std::string message, ...);
    void AK_API Warning(std::string message, ...);
    void AK_API Strong_Warning(std::string message, ...);
    void AK_API Message(std::string message, ...);
}

#define AK_BEGIN_SESSION(name) Ak::Core::log::report("Begin " name " ----")
#define AK_END_SESSION() Ak::Core::log::report("End ----")

#endif // __AK_LOG__
