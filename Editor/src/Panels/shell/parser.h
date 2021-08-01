// This file is a part of the Akel editor
// CREATED : 10/07/2021
// UPDATED : 30/07/2021

#ifndef __AK_SHELL_PARSER__
#define __AK_SHELL_PARSER__

#include <AkEpch.h>

enum class Commands
{
	clear = 0x01,
	help = 0x02,
	history = 0x03,
	build = 0x04,
	sysShell = 0x05,
	quit = 0x06,
	error = 0x07,
	easterEgg = 0x08,
};

class Parser
{
	public:
		Parser() = default;
		uint8_t parse(std::string command);
		~Parser() = default;

	private:
		static inline Ak::duets_array<Commands, std::string> _keywords
		{
			{Commands::clear, "clear"},
			{Commands::help, "help"},
			{Commands::history, "history"},
			{Commands::build, "build"},
			{Commands::sysShell, "sysShell"},
			{Commands::quit, "quit"},
			{Commands::easterEgg, "kbz_8"}
		};

		std::stringstream _stream;
};

#endif // __AK_SHELL_PARSER__
