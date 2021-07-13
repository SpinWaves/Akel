// This file is a part of the Akel editor
// CREATED : 10/07/2021
// UPDATED : 12/07/2021

#include <Panels/shell/shell.h>

uint8_t Parser::parse(std::string command)
{
	_stream << command;
	std::string data;
	_stream >> data;
	if(_keywords.have(data))
	{
		std::cout << command << std::endl;
		if(_stream >> data) // Args management
		{
			_stream.clear();
			if(_keywords.have(data))
			{
				std::cout << std::string(command.begin(), command.begin() + command.find(" ")) << std::endl;
				return static_cast<uint8_t>(_keywords[std::string(command.begin(), command.begin() + command.find(" "))]) | static_cast<uint8_t>(_keywords[data]);
			}
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

