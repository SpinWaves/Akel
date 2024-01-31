// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 31/01/2024

#ifndef __AK_CORE_LOGS__
#define __AK_CORE_LOGS__

#include <Core/PreCompiled.h>

namespace Ak::Log
{
	AK_CORE_API void Debug(std::string message, ...);
	AK_CORE_API void Error(std::string message, ...);
	AK_CORE_API void Warning(std::string message, ...);
	AK_CORE_API void Message(std::string message, ...);
	AK_CORE_API void FatalError(std::string message, ...);
}

#endif
