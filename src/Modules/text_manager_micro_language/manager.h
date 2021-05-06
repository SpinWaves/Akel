// This file is a part of AtlasEngine
// CREATED : 05/05/2021
// UPDATED : 05/05/2021

#ifndef __MICRO_TEXT_LANGUAGE__
#define __MICRO_TEXT_LANGUAGE__

#include <AEpch.h>

namespace AE::TL
{
	class TextLanguage
	{
		public:
			TextLanguage(const char file);

			std::string getText(std::string ID);

		private:
			const char* file;
			std::map<std::string, std::string> _IDs_Texts;
			std::map<std::string, bool> _keyCodes;
	};
}

#endif // __MICRO_TEXT_LANGUAGE__

