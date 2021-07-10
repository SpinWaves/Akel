// This file is a part of the Akel editor
// CREATED : 10/07/2021
// UPDATED : 10/07/2021

#ifndef __AK_SHELL_PARSER__
#define __AK_SHELL_PARSER__

#include <AkEpch.h>

enum class Commands
{
	clear = 0x00,
	help = 0x01,
	history = 0x02,
	build = 0x04,
	sysShell = 0x08,
	quit = 0xF0,
};

class Parser
{
	public:
		Parser() = default;
		uint8_t parse(std::string command);

	private:
		static inline Ak::duets_array<Commands, std::string> _keywords
		{
			{Commands::clear, "clear"},
			{Commands::help, "help"},
			{Commands::history, "history"},
			{Commands::build, "build"},
			{Commands::sysShell, "sysShell"},
			{Commands::quit, "quit"}
		};

		std::stringstream _stream;
};

#endif // __AK_SHELL_PARSER__

