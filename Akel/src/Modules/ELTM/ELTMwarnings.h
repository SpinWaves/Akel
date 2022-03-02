// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/05/2021
// Updated : 13/07/2021

#ifndef __AK_ELTM_WARNING__
#define __AK_ELTM_WARNING__

#include <Akpch.h>

namespace Ak
{
	class ELTMwarning
	{
		public:
			ELTMwarning(std::string message, std::string file, std::string caller, size_t line);
			const char* what();
			size_t line();
			const char* file();
			const char* caller();
			
		private:
			size_t _line;
			std::string _message;
			std::string _caller;
			std::string _file;
	};

	ELTMwarning no_end(std::string message, std::string file, size_t line); 
}

#endif // __AK_ELTM_WARNING__

