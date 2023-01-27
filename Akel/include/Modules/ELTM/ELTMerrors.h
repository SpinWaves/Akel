// This file is a part of Akel
// Authors : @kbz_8
// Created : 13/05/2021
// Updated : 28/08/2022

#ifndef __AK_ELTM_ERRORS__
#define __AK_ELTM_ERRORS__

#include <Akpch.h>
#include <Utils/utils.h>

namespace Ak
{
	class ELTMerrors
	{
		public:
			ELTMerrors(std::string message, std::string file, std::string caller, std::size_t line);

			inline void expose()
			{
				std::cout	<< "\x1b[38;2;255;25;25m" << "[ELTM error] " << def
							<< _message 
							<< " at line " << _line + 1;
				if(!_caller.empty())
					std::cout << " in function \"" << _caller << '"';
				std::cout << " in file " << _file << std::endl;
			}

		private:
			std::string _file;
			std::string _caller;
			std::string _message;
			std::size_t _line;
	};

	ELTMerrors syntax_error(std::string message, std::string file, std::size_t line);
	ELTMerrors unexpected_error(std::string message, std::string file, std::size_t line);
	ELTMerrors expected_syntax_error(std::string message, std::string file, std::size_t line);
	ELTMerrors file_not_found_error(std::string message, std::string file, std::size_t line);
	ELTMerrors context_error(std::string message, std::string file, std::string caller, std::size_t line);
	ELTMerrors already_declared_error(std::string message, std::string file, std::size_t line);
	ELTMerrors unknown_id_error(std::string message, std::string file, std::size_t line);
}

#endif // __AK_ELTM_ERRORS__

