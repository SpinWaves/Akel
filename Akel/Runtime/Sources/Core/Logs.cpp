// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Core/Logs.h>
#include <Utils/Ansi.h>
#include <Core/EventBase.h>
#include <Core/EventBus.h>

namespace Ak
{
	namespace Internal
	{
		struct FatalErrorEvent : public EventBase
		{
			std::uint32_t What() const override { return 167; }
		};
	}

	void Logs::Report(LogType type, std::string message)
	{
		Report(type, 0, {}, {}, std::move(message));
	}

	void Logs::Report(LogType type, unsigned int line, std::string_view file, std::string_view function, std::string message)
	{
		using namespace std::literals;

		#ifndef AK_CORE_DEBUG
			if(type == LogType::Debug)
				return;
		//	if(type != WARNING)
		//		MessageBox(type, "Akel logs recieved a report", buffer, false);
		#endif

		std::string code_infos;
		#ifdef AK_CORE_DEBUG
			if((type == LogType::Error || type == LogType::FatalError) && !file.empty() && !function.empty())
			{
				code_infos += "{in file '"s;
				code_infos += file;
				code_infos += "', line "s + std::to_string(line) + ", in function '"s;
				code_infos += function;
				code_infos += "'} "s;
			}
		#endif

		switch(type)
		{
			case LogType::Debug: std::cout << Ansi::blue << "[Akel Debug] " << Ansi::def << code_infos << message << '\n'; break;
			case LogType::Message: std::cout << Ansi::blue << "[Akel Message] " << Ansi::def << code_infos << message << '\n'; break;
			case LogType::Warning: std::cout << Ansi::magenta << "[Akel Warning] " << Ansi::def << code_infos << message << '\n'; break;
			case LogType::Error: std::cerr << Ansi::red << "[Akel Error] " << Ansi::def << code_infos << message << '\n'; break;
			case LogType::FatalError: std::cerr << Ansi::red << "[Akel Fatal Error] " << Ansi::def << code_infos << message << '\n'; break;

			default: break;
		}
		if(type == LogType::FatalError)
		{
			std::cout << Ansi::bg_red << "Fatal Error: emergency exit" << Ansi::bg_def << std::endl;
			EventBus::Send("__internal_memory_manager", Internal::FatalErrorEvent{});
		}
	}
}
