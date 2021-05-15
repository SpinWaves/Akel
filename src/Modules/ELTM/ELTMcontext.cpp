// This file is a part of AtlasEngine
// CREATED : 12/05/2021
// UPDATED : 15/05/2021

#include <Modules/ELTM/eltm.h>

namespace AE
{
	ELTMcontext::ELTMcontext() : stream()
	{}

	bool ELTMcontext::newContext(const char* file)
	{
		stream.tokenize(file);
		std::string text;
		for(int i = 0; i <= stream.getLineNumber(); i++)
		{
			if(stream.getToken(i, 0).isKeyword())
			{
				switch(stream.getToken(i, 0).getReservedToken())
				{
					case kw_set:
					{
						if(stream.getToken(i, 2).getReservedToken() == assign)
						{
							for(int j = 3; j <= stream.getLineIndexNumber(i); j++)
							{
								text += stream.getToken(i, j).getString();
								text += " ";
							}
							texts[stream.getToken(i, 1).getString()] = text;
						}
						else
						{
							ELTMerrors error = syntax_error("missing \"=\" after ID declaration", file, stream.getToken(i, 0).getLine()+1);
							std::cout << red << error.what() << def << std::endl;
							return false;
						}
						break;
					}

					default: break;
				}
			}
		}
		return true;
	}
}

