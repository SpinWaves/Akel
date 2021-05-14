// This file is a part of AtlasEngine
// CREATED : 13/05/2021
// UPDATED : 14/05/2021

#include <Modules/ELTM/eltm.h>

namespace AE
{
	ELTMerrors::ELTMerrors(std::string message, size_t line)
	{
		_message = std::move(message);
		_line = line;
	}

	const char* ELTMerrors::what()
	{
		return _message.c_str();
	}

	size_t ELTMerrors::line()
	{
		return _line;
	}

	ELTMerrors syntax_error(std::string message, size_t line)
	{
		std::string _message = std::string("ELTM syntax error, line : " + std::to_string(line) + " ");
		_message += message;
		return ELTMerrors(std::move(_message), line);
	}
	ELTMerrors file_not_found_error(std::string message, size_t line)
	{
		std::string _message = std::string("ELTM error, line : " + std::_tostring(line) + " \"");
		_message += message;
		_message += "\" file not found";
		return ELTMerrors(std::move(_message), line);
	}
	ELTMerrors context_error(std::string message, size_t line)
	{
		std::string _message = std::string("ELTM context error, line : " + std::to_string(line) + ", ");
		_message += message;
		return ELTMerrors(std::move(_message), line);
	}
}

