// This file is a part of Akel
// CREATED : 23/06/2021
// UPDATED : 24/06/2021

#include <Core/Components/components.h>

namespace Ak
{
	Component::Component(const char* name)
	{
		_name = name;
	}
	const char* Component::getName()
	{
		return _name;
	}
}

