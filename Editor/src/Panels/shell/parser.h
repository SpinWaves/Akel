// This file is a part of the Akel editor
// Author : @kbz_8
// CREATED : 10/07/2021
// UPDATED : 02/08/2021

#ifndef __AK_SHELL_PARSER__
#define __AK_SHELL_PARSER__

#include <AkEpch.h>

enum class Commands
{
	clear = 0x00001,
	help = 0x00002,
	history = 0x00004,
	build = 0x00008,
	sysShell = 0x00010,
	quit = 0x00020,
	error = 0x00040,
	easterEgg = 0x00080,
	release = 0x00100,
	debug = 0x00200,
};

class Parser
{
	public:
		Parser() = default;
		uint16_t parse(std::string command);
		std::string getOption();
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
			{Commands::easterEgg, "Rick"}
		};

		std::stringstream _stream;
		std::string _option = "";
};

#endif // __AK_SHELL_PARSER__
