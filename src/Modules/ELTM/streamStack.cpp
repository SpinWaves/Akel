// This file is a part of AtlasEngine
// CREATED : 08/05/2021
// UPDATED : 17/05/2021

#include <Modules/ELTM/eltm.h>

namespace AE
{
	int StreamStack::getLineIndexNumber(int line)
	{
		return _lines_indexes[line].size();
	}

	int StreamStack::getTokenNumber()
	{
		return _tokens.size();
	}

	int StreamStack::getLineNumber()
	{
		return _lines_indexes.size();
	}
}

