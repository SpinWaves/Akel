// This file is a part of Akel
// CREATED : 10/06/2021
// UPDATED : 12/08/2021

#include <Core/core.h>
#include <Utils/utils.h>

namespace Ak
{
	Application::Application(const char* name) : ComponentStack()
	{
		add_component(custom_malloc<CounterFPS>());
		_name = name;
		if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
			Core::log::report(FATAL_ERROR, std::string("SDL error : unable to init all subsystems : ") + SDL_GetError());
	}

	void Application::run()
	{
		ImGuiComponent imgui;
		Input in;
		while(!in.isEnded()) // Main loop
		{
        	while(SDL_PollEvent(in.getNativeEvent()))
			{
				in.update();
				for(auto elem : _components)
					elem->onEvent(in);
			}
			for(auto elem : _components)
				elem->update();

			imgui.begin();
				for(auto elem : _components)
					elem->onImGuiRender();
			imgui.end();
		}

		for(auto elem : _components)
			elem->onQuit();
	}

	Application::~Application()
	{
		if(SDL_WasInit(SDL_INIT_EVERYTHING))
			SDL_Quit();
	}
}
