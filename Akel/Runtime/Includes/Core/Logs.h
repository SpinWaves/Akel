// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 01/02/2024

#ifndef __AK_CORE_LOGS__
#define __AK_CORE_LOGS__

#include <Core/PreCompiled.h>
#include <Core/Enums.h>

namespace Ak
{
	template<typename... Args>
	void Debug(std::string message, unsigned int line, std::string_view file, std::string_view function, const Args&... args);

	template<typename... Args>
	void Error(std::string message, unsigned int line, std::string_view file, std::string_view function, const Args&... args);

	template<typename... Args>
	void Warning(std::string message, unsigned int line, std::string_view file, std::string_view function, const Args&... args);

	template<typename... Args>
	void Message(std::string message, unsigned int line, std::string_view file, std::string_view function, const Args&... args);

	template<typename... Args>
	void FatalError(std::string message, unsigned int line, std::string_view file, std::string_view function, const Args&... args);

	class AK_CORE_API Logs
	{
		public:
			Logs() = delete;

			static void Report(LogType type, std::string message);
			static void Report(LogType type, unsigned int line, std::string_view file, std::string_view function, std::string message);

			~Logs() = delete;
	};
}

#include <Core/Logs.inl>

namespace Ak
{
	#undef  Debug
	#define Debug(msg, ...) Debug(msg, __LINE__ - 1, __FILE__, AK_FUNC_SIG, __VA_ARGS__)

	#undef  Message
	#define Message(msg, ...) Message(msg, __LINE__ - 1, __FILE__, AK_FUNC_SIG, __VA_ARGS__)

	#undef  Warning
	#define Warning(msg, ...) Warning(msg, __LINE__ - 1, __FILE__, AK_FUNC_SIG, __VA_ARGS__)

	#undef  Error
	#define Error(msg, ...) Error(msg, __LINE__ - 1, __FILE__, AK_FUNC_SIG, __VA_ARGS__)

	#undef  FatalError
	#define FatalError(msg, ...) FatalError(msg, __LINE__ - 1, __FILE__, AK_FUNC_SIG, __VA_ARGS__)
}

#endif
