// This file is a part of AtlasEngine
// CREATED : 13/05/2021
// UPDATED : 14/05/2021

#ifndef __ELTM_ERRORS__
#define __ELTM_ERRORS__

#include <AEpch.h>

namespace AE
{
	class ELTMerrors
	{
		public:
			ELTMerrors(std::string message, std::string file, std::string caller, size_t line);
			const char* what();
			size_t line();
			std::string file();
			std::string caller();

		private:
			size_t _line;
			std::string _file;
			std::string _caller;
			std::string _message;
	};

	ELTMerrors syntax_error(std::string message, std::string file, size_t line);
	ELTMerrors file_not_found_error(std::string message, std::string file, size_t line);
	ELTMerrors context_error(std::string message, std::string file, std::string caller, size_t line);
}

#endif // __ELTM_ERRORS__

