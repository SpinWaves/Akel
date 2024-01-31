// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 31/01/2024

#include <Core/Logs.h>
#include <Utils/Ansi.h>

namespace Ak::Logs
{
	constexpr const std::uint8_t DEBUGLOG = 0;
	constexpr const std::uint8_t MESSAGE = 1;
	constexpr const std::uint8_t WARNING = 2;
	constexpr const std::uint8_t ERROR = 3;
	constexpr const std::uint8_t FATAL_ERROR = 4;

	constexpr const std::uint32_t BUFFER_SIZE = 1024;

	namespace Internal
	{
		void report(std::uint8_t type, std::string message)
		{
			#ifndef AK_DEBUG
				if(type == DEBUGLOG)
					return;
				if(type != WARNING)
					MessageBox(type, "Akel logs recieved a report", buffer, false);
			#endif

			switch(type)
			{
				case DEBUGLOG: std::cout << Ansi::blue << "[Akel Debug] " << Ansi::def << message << '\n'; break;
				case MESSAGE: std::cout << Ansi::blue << "[Akel Message] " << Ansi::def << message << '\n'; break;
				case WARNING: std::cout << Ansi::magenta << "[Akel Warning] " << Ansi::def << message << '\n'; break;
				case ERROR: std::cerr << Ansi::red << "[Akel Error] " << Ansi::def << message << '\n'; break;
				case FATAL_ERROR: std::cerr << Ansi::red << "[Akel Fatal Error] " << Ansi::def << message << '\n'; break;

				default: break;
			}
			if(type == FATAL_ERROR)
			{
				std::cout << Ansi::bg_red << "Fatal Error: emergency exit" << Ansi::bg_def << std::endl;
			}
		}
	}

	void Debug(std::string message, ...)
	{
		std::string buffer(message.length() + BUFFER_SIZE, 0);
		std::va_list args;
		va_start(args, message);
		std::vsprintf(buffer.data(), message.c_str(), args);
		va_end(args);

		Internal::report(DEBUGLOG, std::move(buffer));
	}

	void Error(std::string message, ...)
	{
		std::string buffer(message.length() + BUFFER_SIZE, 0);
		std::va_list args;
		va_start(args, message);
		std::vsprintf(buffer.data(), message.c_str(), args);
		va_end(args);

		Internal::report(ERROR, std::move(buffer));
	}

	void Warning(std::string message, ...)
	{

		std::string buffer(message.length() + BUFFER_SIZE, 0);
		std::va_list args;
		va_start(args, message);
		std::vsprintf(buffer.data(), message.c_str(), args);
		va_end(args);

		Internal::report(WARNING, std::move(buffer));
	}

	void Message(std::string message, ...)
	{

		std::string buffer(message.length() + BUFFER_SIZE, 0);
		std::va_list args;
		va_start(args, message);
		std::vsprintf(buffer.data(), message.c_str(), args);
		va_end(args);

		Internal::report(MESSAGE, std::move(buffer));
	}

	void FatalError(std::string message, ...)
	{

		std::string buffer(message.length() + BUFFER_SIZE, 0);
		std::va_list args;
		va_start(args, message);
		std::vsprintf(buffer.data(), message.c_str(), args);
		va_end(args);

		Internal::report(FATAL_ERROR, std::move(buffer));
	}

}
