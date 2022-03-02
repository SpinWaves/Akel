// This file is a part of Akel
// Author : @kbz_8
// CREATED : 08/05/2021
// UPDATED : 19/05/2021

#include <Modules/ELTM/eltm.h>

namespace Ak
{
	int StreamStack::getLineIndexNumber(int line)
	{
		return _tokens[line].size();
	}

	int StreamStack::getTokenNumber()
	{
		int returner = 0;
		for(int i = 0; i < _tokens.size(); i++)
		{
			returner += _tokens[i].size();
		}
		return returner;
	}

	int StreamStack::getLineNumber()
	{
		return _tokens.size();
	}
}

