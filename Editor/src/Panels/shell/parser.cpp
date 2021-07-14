// This file is a part of the Akel editor
// CREATED : 10/07/2021
// UPDATED : 14/07/2021

#include <Panels/shell/shell.h>

uint8_t Parser::parse(std::string command)
{
	_stream << command;
	std::string data;
	_stream >> data;
	size_t found = 0;
	if((found = data.find(" ")) != std::string::npos)
	{
		std::cout << "test" << std::endl;
		data.erase(data.begin() + found, data.end());
	}
	if(_keywords.have(data))
	{
		if(_stream >> data) // Args management
		{
			_stream.clear();
			if(_keywords.have(data))
				return static_cast<uint8_t>(_keywords[std::string(command.begin(), command.begin() + command.find(" "))]) | static_cast<uint8_t>(_keywords[data]);
			else
				return static_cast<uint8_t>(_keywords[std::string(command.begin(), command.begin() + command.find(" "))]) | static_cast<uint8_t>(Commands::error);
		}
		else
		{
			_stream.clear();
			return static_cast<uint8_t>(_keywords[command]);
		}
	}
	_stream.clear();
	return 0;
}
