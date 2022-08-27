// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/07/2021
// Updated : 27/08/2022

#include <Panels/shell/shell.h>

Shell::Shell(std::shared_ptr<Ak::ELTM> eltm) : Parser()
{
	_eltm = eltm;
}

void Shell::command(std::string command)
{
	ee = false;
	print("> " + command);
	const uint16_t type = Parser::parse(command);
	if(type & static_cast<uint16_t>(Commands::help))
	{
		if(type & static_cast<uint16_t>(Commands::clear))
			print(_eltm->getText("Console.helpClear"), 2);
		else if(type & static_cast<uint16_t>(Commands::history))
			print(_eltm->getText("Console.helpHistory"), 2);
		else if(type & static_cast<uint16_t>(Commands::build))
			print(_eltm->getText("Console.helpBuild"), 2);
		else if(type & static_cast<uint16_t>(Commands::sysShell))
			print(_eltm->getText("Console.helpSysShell"), 2);
		else if(type & static_cast<uint16_t>(Commands::quit))
			print(_eltm->getText("Console.helpQuit"), 2);
		else if(type & static_cast<uint16_t>(Commands::error))
			print("help: " + _eltm->getText("errors.consoleUnknownCommand"), 1);
		else
			print(" " + _eltm->getText("Console.help"), 2);
	}
	else if(type & static_cast<uint16_t>(Commands::clear))
	{
		_history = _out;
		_out.clear();
	}
	else if(type & static_cast<uint16_t>(Commands::history))
		_out.insert(_out.end(), _history.begin(), _history.end());
	else if(type & static_cast<uint16_t>(Commands::build)) {}
	else if(type & static_cast<uint16_t>(Commands::sysShell)) {}
	else if(type & static_cast<uint16_t>(Commands::quit))
		_quit = true;
	else if(type & static_cast<uint16_t>(Commands::easterEgg))
	{
		print("RICK ROLL TIME !!!" , 2);
		ee = true;
	}
	else
		print(_eltm->getText("errors.consoleUnknownCommand"), 1);
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
