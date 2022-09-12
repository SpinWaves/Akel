// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/07/2021
// Updated : 12/09/2022

#include <Panels/shell/shell.h>

Command Parser::parse(std::string command)
{
	std::stringstream stream(std::move(command));
	std::string data;

	_options.clear();
	_arguments.clear();

	stream >> data;
	if(!_keywords.has(data))
		return Command::error;

	Command com = _keywords[data];

	while(stream >> data)
	{
		if(data[0] == '-')
			_options.push_back(data);
		else
		{
			if(_keywords.has(data))
				_arguments.push_back(_keywords[data]);
			else
				_arguments.push_back(data);
		}
	}

	return com;
}
