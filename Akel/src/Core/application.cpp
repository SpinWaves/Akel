// This file is a part of Akel
// CREATED : 10/06/2021
// UPDATED : 27/06/2021

#include <Core/core.h>
#include <Platform/messageBox.h>

namespace Ak
{
	Application::Application(const char* name) : ComponentStack()
	{
		_name = name;
	}

	void Application::run()
	{
		messageBox(MESSAGE, "tset", "louloulou");
		while(_running)
		{
			for(auto elem : _components)
				elem->update();
			_running = false;
		}
	}
}

