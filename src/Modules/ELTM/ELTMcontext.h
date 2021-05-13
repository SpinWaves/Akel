// This file is a part of AtlasEngine
// CREATED : 12/05/2021
// UPDATED : 13/05/2021

#ifndef __ELTM_CONTEXT__
#define __ELTM_CONTEXT__

#include <AEpch.h>

namespace AE
{
	class ELTMcontext
	{
		public:
			ELTMcontext();
			bool newContext(const char* file);
			std::string getText(std::string ID);

		private:
			std::map<std::string, std::string> texts;
			std::map<std::string, std::map<std::string, std::string>> modules;
			StreamStack stream;
	};
}

#endif // __ELTM_CONTEXT__

