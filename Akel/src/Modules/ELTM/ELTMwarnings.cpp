// This file is a part of Akel
// Author : @kbz_8
// CREATED : 20/05/2021
// UPDATED : 20/05/2021

#include <Modules/ELTM/eltm.h>

namespace Ak
{
	ELTMwarning::ELTMwarning(std::string message, std::string file, std::string caller, size_t line)
	{
		_message = message;
		_line = line;
		_caller = caller;
		_file = file;
	}

	const char* ELTMwarning::what()
	{
		return _message.c_str();
	}

	const char* ELTMwarning::file()
	{
		return _file.c_str();
	}

	const char* ELTMwarning::caller()
	{
		return _caller.c_str();
	}
	
	size_t ELTMwarning::line()
	{
		return _line;
	}


	ELTMwarning no_end(std::string message, std::string file, size_t line)
	{
		std::string _message = std::string("ELTM warning, file: " + file + ", line: " + std::to_string(line) + ", " + message + " has been begun without end");
		return ELTMwarning(std::move(_message), file, "", line);
	}
}

