// This file is a part of AtlasEngine
// CREATED : 08/05/2021
// UPDATED : 15/05/2021

#include <Modules/ELTM/eltm.h>

namespace AE
{
	int StreamStack::getLineIndexNumber(int line)
	{
		int returner = 0;
		for(int i = line;; i++)
		{
			if(_tokens[i].getLine() != line)
			{
				returner = i-1;
				break;
			}
		}
		return returner;
	}

	int StreamStack::getTokenNumber()
	{
		return _tokens.size();
	}

	int StreamStack::getLineNumber()
	{
		return _lines;
	}
}

