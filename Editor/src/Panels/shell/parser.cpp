// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 10/07/2021
// Updated : 02/08/2021

#include <Panels/shell/shell.h>

uint16_t Parser::parse(std::string command)
{
	size_t found = 0;
	size_t endOpt = 0;
	_option.clear();
	if((found = command.find(" -")) != std::string::npos)
	{
		if((endOpt = command.find(" ", found + 2)) == std::string::npos)
			endOpt = command.length();

		_option.insert(_option.begin(), command.begin() + found + 2, command.begin() + endOpt);
		command.erase(command.begin() + found, command.begin() + endOpt);
	}

	_stream << command;
	std::string data;
	_stream >> data;
	if(_keywords.have(data))
	{
		if(_stream >> data) // Args management
		{
			_stream.clear();
			if(_keywords.have(data))
				return static_cast<uint16_t>(_keywords[std::string(command.begin(), command.begin() + command.find(" "))]) | static_cast<uint8_t>(_keywords[data]);
			else
				return static_cast<uint16_t>(_keywords[std::string(command.begin(), command.begin() + command.find(" "))]) | static_cast<uint8_t>(Commands::error);
		}
		else
		{
			_stream.clear();
			return static_cast<uint16_t>(_keywords[command]);
		}
	}
	_stream.clear();
	return 0;
}

std::string Parser::getOption()
{
	return _option;
}
