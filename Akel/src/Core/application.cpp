// This file is a part of Akel
// CREATED : 10/06/2021
// UPDATED : 25/06/2021

#include <Core/core.h>

namespace Ak
{
	Application::Application(const std::string name) : ComponentStack()
	{
		_name = name;
	}

	void Application::run()
	{
		while(_running)
		{
			for(auto elem : _components)
				elem->update();
		}
	}
}

