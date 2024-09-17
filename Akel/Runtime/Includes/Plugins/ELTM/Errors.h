// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_ELTM_ERRORS__
#define __AK_ELTM_ERRORS__

#include <Plugins/ELTM/PreCompiled.h>
#include <Utils/Ansi.h>

namespace Ak
{
	class ELTMerror
	{
		public:
			ELTMerror(std::string message, std::string file, std::string caller, std::size_t line);
			inline void Expose()
			{
				std::cout	<< "\x1b[38;2;255;25;25m" << "[ELTM error] " << Ansi::def
							<< m_message 
							<< " at line " << m_line + 1;
				if(!m_caller.empty())
					std::cout << " in function \"" << m_caller << '"';
				std::cout << " in file " << m_file << std::endl;
			}

		private:
			std::string m_file;
			std::string m_caller;
			std::string m_message;
			std::size_t m_line;
	};

	ELTMerror SyntaxError(std::string message, std::string file, std::size_t line);
	ELTMerror UnexpectedError(std::string message, std::string file, std::size_t line);
	ELTMerror ExpectedSyntaxError(std::string message, std::string file, std::size_t line);
	ELTMerror FileNotFoundError(std::string message, std::string file, std::size_t line);
	ELTMerror ContextError(std::string message, std::string file, std::string caller, std::size_t line);
	ELTMerror AlreadyDeclaredError(std::string message, std::string file, std::size_t line);
	ELTMerror UnknownIdError(std::string message, std::string file, std::size_t line);
}

#endif
