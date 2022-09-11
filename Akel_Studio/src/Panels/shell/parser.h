// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/07/2021
// Updated : 11/09/2022

#ifndef __AK_SHELL_PARSER__
#define __AK_SHELL_PARSER__

#include <AkSpch.h>

enum class Command
{
	clear,
	help,
	history,
	build,
	sysShell,
	quit,
	error,
	easterEgg,
};

class Parser
{
	public:
		Parser() = default;
		Command parse(std::string command);
		inline const std::string& getOption(int index) { return _option[index]; }
		inline const std::variant<std::string, Command>& getArg(int index) { return _arguments[index]; }
		~Parser() = default;

	private:
		static inline Ak::duets_array<Command, std::string> _keywords
		{
			{Commands::clear, "clear"},
			{Commands::help, "help"},
			{Commands::history, "history"},
			{Commands::build, "build"},
			{Commands::sysShell, "sysShell"},
			{Commands::quit, "quit"},
			{Commands::easterEgg, "rick"}
		};

		std::vector<std::string> _options;
		std::vector<std::variant<std::string, Command>> _arguments;
};

#endif // __AK_SHELL_PARSER__
