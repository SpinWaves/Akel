// This file is a part of Akel
// Authors : @kbz_8
// Created : 13/05/2021
// Updated : 26/08/2022

#include <Modules/ELTM/eltm.h>

namespace Ak
{
	ELTMerrors::ELTMerrors(std::string message, std::string file, std::string caller, std::size_t line) :
		_message(std::move(message)),
		_line(line),
		_file(std::move(file)),
		_caller(std::move(caller))
	{}

	ELTMerrors syntax_error(std::string message, std::string file, std::size_t line)
	{
		message.insert(0, "syntax error, ");
		return ELTMerrors(std::move(message), std::move(file), "", line);
	}
	ELTMerrors unexpected_error(std::string message, std::string file, std::size_t line)
	{
		message.insert(0, "unexpected ");
		return ELTMerrors(std::move(message), std::move(file), "", line);
	}
	ELTMerrors file_not_found_error(std::string message, std::string file, std::size_t line)
	{
		message.insert(0, "file not found '");
		message.push_back('\'');
		return ELTMerrors(std::move(message), std::move(file), "", line);
	}
	ELTMerrors context_error(std::string message, std::string file, std::string caller, std::size_t line)
	{
		message.insert(0, "context error, ");
		return ELTMerrors(std::move(message), std::move(file), std::move(caller), line);
	}
	ELTMerrors already_declared_error(std::string message, std::string file, std::size_t line)
	{
		message += " is already declared in this scope";
		return ELTMerrors(std::move(message), std::move(file), "", line);
	}
}

