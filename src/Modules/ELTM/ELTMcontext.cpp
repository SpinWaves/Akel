// This file is a part of AtlasEngine
// CREATED : 12/05/2021
// UPDATED : 14/05/2021

#include <Modules/ELTM/eltm.h>

namespace AE
{
	ELTMcontext::ELTMcontext() : stream()
	{}

	bool ELTMcontext::newContext(const char* file)
	{
		stream.tokenize(file);
		std::string text;
		for(int i = 0; i < stream.getTokenNumber(); i++)
		{
			for(int j = 0; j < stream.getLineIndexNumber(i); j++)
			{
				if(stream.getToken(i, j).isKeyword())
				{
					switch(stream.getToken(i, j).getReservedToken())
					{
						case kw_set:
							std::cout << stream.getToken(i, stream.getLineIndexNumber(i)).getString() << std::endl;
							for(int k = 3; k < stream.getLineIndexNumber(i); k++)
							{
								text.append(stream.getToken(i, k).getString());
							//	std::cout << stream.getToken(i, k).getString() << std::endl;
							}
							texts[stream.getToken(i, j+1).getString()] = text;
						break;

						default: break;
					}
				}
			}
		}
		std::cout << texts["test"] << std::endl;
		return true;
	}
}

