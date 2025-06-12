// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef AK_CORE_LOGS_H
#define AK_CORE_LOGS_H

#include <Core/PreCompiled.h>
#include <Core/Enums.h>

namespace Ak
{
	template<typename... Args>
	void DebugLog(unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args);

	template<typename... Args>
	void Error(unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args);

	template<typename... Args>
	void Warning(unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args);

	template<typename... Args>
	void Message(unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args);

	template<typename... Args>
	void FatalError(unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args);

	template<typename... Args>
	void Verify(bool cond, unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args);

	class AK_CORE_API Logs
	{
		public:
			Logs() = delete;

			static void Report(LogType type, std::string message);
			static void Report(LogType type, unsigned int line, std::string_view file, std::string_view function, std::string message);

			~Logs() = delete;
	};

	#if defined(AK_CORE_DEBUG) || defined(AK_FORCE_ENABLE_ASSERTS)
		template<typename... Args>
		void Assert(bool cond, unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args);
	#else
		template<typename... Args>
		void Assert(bool cond, unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args) {}
	#endif
}

#include <Core/Logs.inl>

namespace Ak
{
	#undef  DebugLog
	#define DebugLog(...) DebugLog(__LINE__, __FILE__, AK_FUNC_SIG, __VA_ARGS__)

	#undef  Message
	#define Message(...) Message(__LINE__, __FILE__, AK_FUNC_SIG, __VA_ARGS__)

	#undef  Warning
	#define Warning(...) Warning(__LINE__, __FILE__, AK_FUNC_SIG, __VA_ARGS__)

	#undef  Error
	#define Error(...) Error(__LINE__, __FILE__, AK_FUNC_SIG, __VA_ARGS__)

	#undef  FatalError
	#define FatalError(...) FatalError(__LINE__, __FILE__, AK_FUNC_SIG, __VA_ARGS__)

	#undef  Verify
	#define Verify(cond, ...) Verify(cond, __LINE__, __FILE__, AK_FUNC_SIG, __VA_ARGS__)

	#undef  Assert
	#define Assert(cond, ...) Assert(cond, __LINE__, __FILE__, AK_FUNC_SIG, __VA_ARGS__)
}

#endif
