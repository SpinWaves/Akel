// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/07/2021
// Updated : 12/09/2022

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
		inline const std::vector<std::string>& getOptions() { return _options; }
		inline const std::vector<std::variant<std::string, Command>>& getArg() { return _arguments; }
		~Parser() = default;

	protected:
		static inline Ak::duets_array<Command, std::string> _keywords
		{
			{Command::clear, "clear"},
			{Command::help, "help"},
			{Command::history, "history"},
			{Command::build, "build"},
			{Command::sysShell, "sysShell"},
			{Command::quit, "quit"},
			{Command::easterEgg, "rick"}
		};

	private:
		std::vector<std::string> _options;
		std::vector<std::variant<std::string, Command>> _arguments;
};

#endif // __AK_SHELL_PARSER__
