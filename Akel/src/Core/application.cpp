// This file is a part of Akel
// CREATED : 10/06/2021
// UPDATED : 28/06/2021

#include <Core/core.h>

namespace Ak
{
	Application::Application(const char* name) : ComponentStack(), _in()
	{
		_name = name;
	}

	void Application::run()
	{
		while(!_in.isEnded()) // Main loop
		{
			_in.update();
			for(auto elem : _components)
			{
				elem->onEvent(_in);
				elem->update();
			}
		}

		for(auto elem : _components)
			elem->onQuit();
	}
}

