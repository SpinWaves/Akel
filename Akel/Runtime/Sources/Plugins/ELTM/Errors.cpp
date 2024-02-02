// This file is a part of Akel
// Authors : @kbz_8
// Created : 13/05/2021
// Updated : 02/02/2024

#include <Plugins/ELTM/Errors.h>

namespace Ak
{
	ELTMerror::ELTMerror(std::string message, std::string file, std::string caller, std::size_t line) :
		m_message(std::move(message)),
		m_line(line),
		m_file(std::move(file)),
		m_caller(std::move(caller))
	{}

	ELTMerror SyntaxError(std::string message, std::string file, std::size_t line)
	{
		message.insert(0, "syntax error, ");
		return ELTMerror(std::move(message), std::move(file), "", line);
	}

	ELTMerror ExpectedSyntaxError(std::string message, std::string file, std::size_t line)
	{
		message.insert(0, "expected ");
		return ELTMerror(std::move(message), std::move(file), "", line);
	}

	ELTMerror UnexpectedError(std::string message, std::string file, std::size_t line)
	{
		message.insert(0, "unexpected \"");
		message.push_back('"');
		return ELTMerror(std::move(message), std::move(file), "", line);
	}

	ELTMerror FileNotFoundError(std::string message, std::string file, std::size_t line)
	{
		message.insert(0, "file not found '");
		message.push_back('\'');
		return ELTMerror(std::move(message), std::move(file), "", line);
	}

	ELTMerror Contexterror(std::string message, std::string file, std::string caller, std::size_t line)
	{
		message.insert(0, "context error, ");
		return ELTMerror(std::move(message), std::move(file), std::move(caller), line);
	}

	ELTMerror AlreadyDeclaredError(std::string message, std::string file, std::size_t line)
	{
		message += " is already declared in this scope";
		return ELTMerror(std::move(message), std::move(file), "", line);
	}

	ELTMerror UnknownIdError(std::string message, std::string file, std::size_t line)
	{
		message.insert(0, "unknown id '");
		message.push_back('\'');
		return ELTMerror(std::move(message), std::move(file), "", line);
	}
}

