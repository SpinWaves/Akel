// This file is a part of the Akel editor
// CREATED : 10/07/2021
// UPDATED : 10/07/2021

#include <Panels/shell/shell.h>

uint8_t Parser::parse(std::string command)
{
	_stream << std::move(command);
	std::string data;
	_stream >> data;
	if(_keywords.have(data))
	{
		if(_stream >> data)
		{
			std::cout << data << std::endl;
		}
		else
		{
			std::cout << "nope" << std::endl;
			return static_cast<uint8_t>(_keywords[command]);
		}
	}
}

