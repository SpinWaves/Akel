// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once
#include <Core/Logs.h>

#include <Core/Format.h>

namespace Ak
{
	template<typename... Args>
	void DebugLog(unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args)
	{
		using namespace std::literals;
		try
		{
			std::stringstream ss;
			ss << Format(message, args...);
			Logs::Report(LogType::Debug, line, file, function, ss.str());
		}
		catch(const std::exception& e)
		{
			Logs::Report(LogType::Error, "formatter exception catched in the log printer : "s + e.what());
		}
	}

	template<typename... Args>
	void Error(unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args)
	{
		using namespace std::literals;
		try
		{
			std::stringstream ss;
			ss << Format(message, args...);
			Logs::Report(LogType::Error, line, file, function, ss.str());
		}
		catch(const std::exception& e)
		{
			Logs::Report(LogType::Error, "formatter exception catched in the log printer : "s + e.what());
		}
	}

	template<typename... Args>
	void Warning(unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args)
	{
		using namespace std::literals;
		try
		{
			std::stringstream ss;
			ss << Format(message, args...);
			Logs::Report(LogType::Warning, line, file, function, ss.str());
		}
		catch(const std::exception& e)
		{
			Logs::Report(LogType::Error, "formatter exception catched in the log printer : "s + e.what());
		}
	}

	template<typename... Args>
	void Message(unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args)
	{
		using namespace std::literals;
		try
		{
			std::stringstream ss;
			ss << Format(message, args...);
			Logs::Report(LogType::Message, line, file, function, ss.str());
		}
		catch(const std::exception& e)
		{
			Logs::Report(LogType::Error, "formatter exception catched in the log printer : "s + e.what());
		}
	}

	template<typename... Args>
	void FatalError(unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args)
	{
		using namespace std::literals;
		try
		{
			std::stringstream ss;
			ss << Format(message, args...);
			Logs::Report(LogType::FatalError, line, file, function, ss.str());
		}
		catch(const std::exception& e)
		{
			Logs::Report(LogType::Error, "formatter exception catched in the log printer : "s + e.what());
		}
	}

	template<typename... Args>
	void Verify(bool cond, unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args)
	{
		using namespace std::literals;
		if(cond)
			return;
		try
		{
			std::stringstream ss;
			ss << Format("Verification failed : %", message, args...);
			Logs::Report(LogType::FatalError, line, file, function, ss.str());
		}
		catch(const std::exception& e)
		{
			Logs::Report(LogType::Error, "formatter exception catched in the log printer : "s + e.what());
		}
	}

	#if defined(AK_CORE_DEBUG) || defined(AK_FORCE_ENABLE_ASSERTS)
		template<typename... Args>
		void Assert(bool cond, unsigned int line, std::string_view file, std::string_view function, std::string message, const Args&... args)
		{
			using namespace std::literals;
			if(cond)
				return;
			try
			{
				std::stringstream ss;
				ss << Format("Assertion failed : %", message, args...);
				Logs::Report(LogType::FatalError, line, file, function, ss.str());
			}
			catch(const std::exception& e)
			{
				Logs::Report(LogType::Error, "formatter exception catched in the log printer : "s + e.what());
			}
		}
	#endif
}
