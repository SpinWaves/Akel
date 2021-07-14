// This file is a part of the Akel editor
// CREATED : 10/07/2021
// UPDATED : 13/07/2021

#include <Panels/shell/shell.h>

Shell::Shell() : Parser() {}

void Shell::command(std::string command)
{
	print("> " + command);
	const uint8_t type = Parser::parse(command);
	if((type & static_cast<uint8_t>(Commands::help)) == static_cast<uint8_t>(Commands::help))
	{
		if((type & static_cast<uint8_t>(Commands::clear)) == static_cast<uint8_t>(Commands::clear))
			print(Ak::ELTMcontext::getText("Console.helpClear"), 2);
		else if((type & static_cast<uint8_t>(Commands::history)) == static_cast<uint8_t>(Commands::history))
			print(Ak::ELTMcontext::getText("Console.helpHistory"), 2);
		else if((type & static_cast<uint8_t>(Commands::build)) == static_cast<uint8_t>(Commands::build))
			print(Ak::ELTMcontext::getText("Console.helpBuild"), 2);
		else if((type & static_cast<uint8_t>(Commands::sysShell)) == static_cast<uint8_t>(Commands::sysShell))
			print(Ak::ELTMcontext::getText("Console.helpSysShell"), 2);
		else if((type & static_cast<uint8_t>(Commands::quit)) == static_cast<uint8_t>(Commands::quit))
			print(Ak::ELTMcontext::getText("Console.helpQuit"), 2);
		else if((type & static_cast<uint8_t>(Commands::error)) == static_cast<uint8_t>(Commands::error))
			print("help: " + Ak::ELTMcontext::getText("errors.consoleUnknownCommand"), 1);
		else
			print(" " + Ak::ELTMcontext::getText("Console.help"), 2);
	}
	else if((type & static_cast<uint8_t>(Commands::clear)) == static_cast<uint8_t>(Commands::clear))
		_out.clear();
	else if((type & static_cast<uint8_t>(Commands::history)) == static_cast<uint8_t>(Commands::history)) {}
	else if((type & static_cast<uint8_t>(Commands::build)) == static_cast<uint8_t>(Commands::build)) {}
	else if((type & static_cast<uint8_t>(Commands::sysShell)) == static_cast<uint8_t>(Commands::sysShell)) {}
	else if((type & static_cast<uint8_t>(Commands::quit)) == static_cast<uint8_t>(Commands::quit))
		_quit = true;
	else
		print(Ak::ELTMcontext::getText("errors.consoleUnknownCommand"), 1);
}

void Shell::print(std::string print, uint8_t type)
{
	_out.push_back(std::tuple<uint8_t, std::string, __time>(type, print, Ak::Time::getCurrentTime()));
}

std::vector<std::tuple<uint8_t, std::string, __time>> Shell::getOutPut()
{
	return _out;
}

bool Shell::quit()
{
	return _quit;
}

