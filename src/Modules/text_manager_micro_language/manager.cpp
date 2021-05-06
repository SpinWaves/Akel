// This file is a part of AtlasEngine
// CREATED : 05/05/2021
// UPDATED : 05/05/2021

#include <Modules/modules.h>
#include <Platform/platform.h>

namespace AE::TL
{
	TextLanguage::TextLanguage(const char* file)
	{
		// Init keywords codes 
		_keyCodes["long_comment"] = false;
		_keyCodes["basic_comment"] = false;
		_keyCodes["setter"] = false;
		_keyCodes["long_setter"] = false;
		_keyCodes["import"] = false;

		std::string data;
		bool comment = false;
		std::size_t finder;
		std::ifstream getter(file, std::ios::in)
		if(getter)
		{
			while(getter >> data)
			{
				if(data.find("/*") != std::string::npos)
					_keyCodes["long_comment"] = true;

				if(data.find("//") != std::string::npos)
					_keyCodes["basic_comment"] = true;

				if(!_keyCodes["long_comment"] && !_keyCodes["comment"])
				{
				
				}

				if(data.find("*/") != std::string::npos)	
					_keyCodes["long_comment"] = false;

				if(data.find("\n") != std::string::npos && _keyCodes["basic_comment"])
					_keyCodes["basic_comment"] = false;

			}

			getter.close();
		}
		else
			messageBox(ERROR, "Unable to get MicroTextLanguage's file", "oui");
	}
}

