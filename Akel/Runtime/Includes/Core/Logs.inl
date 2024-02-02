// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/02/2024
// Updated : 02/02/2024

#include <Core/Format.h>

namespace Ak
{
	template<typename... Args>
	void Debug(std::string message, unsigned int line, std::string_view file, std::string_view function, const Args&... args)
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
	void Error(std::string message, unsigned int line, std::string_view file, std::string_view function, const Args&... args)
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
	void Warning(std::string message, unsigned int line, std::string_view file, std::string_view function, const Args&... args)
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
	void Message(std::string message, unsigned int line, std::string_view file, std::string_view function, const Args&... args)
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
	void FatalError(std::string message, unsigned int line, std::string_view file, std::string_view function, const Args&... args)
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

	#if defined(AK_CORE_DEBUG) || defined(AK_FORCE_ENABLE_ASSERTS)
		template<typename... Args>
		void Assert(bool cond, std::string message, unsigned int line, std::string_view file, std::string_view function, const Args&... args)
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
