// This file is a part of Akel
// CREATED : 10/06/2021
// UPDATED : 07/07/2021

#include <Core/core.h>
#include <Utils/utils.h>

namespace Ak
{
	Application::Application(const char* name) : ComponentStack(), _in()
	{
		add_component(new CounterFPS);
		_name = name;
		if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
			Core::log::report(FATAL_ERROR, std::string("SDL error : unable to init all subsystems : ") + SDL_GetError());
		_imgui = new ImGuiComponent("Main ImGui");
	}

	void Application::run()
	{
		while(!_in.isEnded()) // Main loop
		{
			_in.update();
			for(auto elem : _components)
			{
				elem->update();
				elem->onEvent(_in);
			}
			_imgui->begin();
				for(auto elem : _components)
					elem->onImGuiRender();
			_imgui->end();
		}

		for(auto elem : _components)
			elem->onQuit();
	}

	Application::~Application()
	{
		delete _imgui;
		if(SDL_WasInit(SDL_INIT_EVERYTHING))
			SDL_Quit();
		std::cout << bg_green << "Akel successfully exited" << bg_def << std::endl;
	}
}

