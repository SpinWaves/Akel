// This file is a part of AtlasEngine
// CREATED : 12/05/2021
// UPDATED : 13/05/2021

#ifndef __ELTM_CONTEXT__
#define __ELTM_CONTEXT__

#include <AEpch.h>
#include <Modules/ELTM/ELTMerrors.h>
#include <Utils/utils.h>

namespace AE
{
	class ELTMcontext
	{
		public:
			ELTMcontext();
			bool newContext(const char* file);
			std::string getText(std::string ID, size_t line, std::string file, std::string function)
			{
				if(texts.count(ID))
					return texts[ID];
				ELTMerrors error = context_error("undefined ID", file, function, line);
				std::cout << red << error.what() << def << std::endl;
				return "error";
			}

		private:
			std::map<std::string, std::string> texts;
			std::map<std::string, std::map<std::string, std::string>> modules;
			StreamStack stream;
	};

	#undef getText
	#define getText(ID) getText(ID, __LINE__, __FILE__, __FUNCTION__)
}

#endif // __ELTM_CONTEXT__

