// This file is a part of AtlasEngine
// CREATED : 13/05/2021
// UPDATED : 17/05/2021

#include <Modules/ELTM/eltm.h>

namespace AE
{
	ELTMerrors::ELTMerrors(std::string message, std::string file, std::string caller, size_t line)
	{
		_message = std::move(message);
		_line = line;
		_file = file;
		_caller = caller;
	}

	const char* ELTMerrors::what()
	{
		return _message.c_str();
	}

	size_t ELTMerrors::line()
	{
		return _line;
	}

	std::string ELTMerrors::file()
	{
		return _file;
	}
	
	std::string ELTMerrors::caller()
	{
		return _caller;
	}

	ELTMerrors syntax_error(std::string message, std::string file, size_t line)
	{
		std::string _message = std::string("ELTM syntax error, file: " + file + ", line: " + std::to_string(line) + ", ");
		_message += message;
		return ELTMerrors(std::move(_message), file, "", line);
	}
	ELTMerrors file_not_found_error(std::string message, std::string file, size_t line)
	{
		std::string _message = std::string("ELTM error, file: " + file + ", line: " + std::to_string(line) +",  \"");
		_message += message;
		_message += "\" file not found";
		return ELTMerrors(std::move(_message), file, "", line);
	}
	ELTMerrors context_error(std::string message, std::string file, std::string caller, size_t line)
	{
		std::string _message = std::string("ELTM context error, file: " + file + ", line: " + std::to_string(line) + ", in function: " + caller + ", ");
		_message += message;
		return ELTMerrors(std::move(_message), file, caller, line);
	}
	ELTMerrors already_declared_error(std::string message, std::string file, size_t line)
	{
		std::string _message = std::string("ELTM error, file: " + file + ", line: " + std::to_string(line) + ", \"" + message + "\" is already declared in this scope");
		return ELTMerrors(std::move(_message), file, "", line);
	}
}

