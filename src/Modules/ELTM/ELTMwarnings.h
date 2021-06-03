// This file is a part of AtlasEngine
// CREATED : 20/05/2021
// UPDATED : 03/06/2021

#ifndef __AE_ELTM_WARNING__
#define __AE_ELTM_WARNING__

#include <AEpch.h>

namespace AE
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

#endif // __AE_ELTM_WARNING__

