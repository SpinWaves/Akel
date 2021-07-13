// This file is a part of the Akel editor
// CREATED : 10/07/2021
// UPDATED : 12/07/2021

#include <Panels/shell/shell.h>

Shell::Shell() : Parser() {}

void Shell::command(std::string command)
{
	uint8_t type = Parser::parse(command);

}

