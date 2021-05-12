// This file is a part of AtlasEngine
// CREATED : 12/05/2021
// UPDATED : 12/05/2021

#ifndef __CONTEXT__
#define __CONTEXT__

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

#endif // __CONTEXT__

