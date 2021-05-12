// This file is a part of AtlasEngine
// CREATED : 12/05/2021
// UPDATED : 12/05/2021

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
							for(int k = 2; k < stream.getLineIndexNumber(i); k++)
							{
								text.append(stream.getToken(i, k).getString());
							}
							texts[stream.getToken(i, j+1).getString()] = text;
						break;
					}
				}
			}
		}
		return true;
	}

	std::string ELTMcontext::getText(std::string ID)
	{
		if(texts.count(ID))
			return texts[ID];
		return "Error : ID undefined";
	}
}

