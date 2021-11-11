// This file is a part of Akel
// CREATED : 10/06/2021
// UPDATED : 11/11/2021

#include <Core/core.h>
#include <Utils/utils.h>
#include <Platform/input.h>
#include <Modules/ImGui/imgui_component.h>
#include <Utils/utils.h>

namespace Ak
{
	Application::Application(const char* name) : ComponentStack(), _in()
	{
		add_component(custom_malloc<CounterFPS>());
		_name = name;
		if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
			Core::log::report(FATAL_ERROR, std::string("SDL error : unable to init all subsystems : ") + SDL_GetError());
	}

	void Application::run()
	{
		ImGuiComponent imgui;
		while(!_in.isEnded()) // Main loop
		{
        	while(SDL_PollEvent(_in.getNativeEvent()))
			{
				_in.update();
				for(auto elem : _components)
					elem->onEvent(_in);
			}
			for(auto elem : _components)
				elem->update();

			if(ImGuiComponent::getNumComp() != 0)
			{
				imgui.begin();
					for(auto elem : _components)
						elem->onImGuiRender();
				imgui.end();
			}
		}

		for(auto elem : _components)
			elem->onQuit();
	}

	void Application::end()
	{
		_in.finish();
	}

	Application::~Application()
	{
		if(SDL_WasInit(SDL_INIT_EVERYTHING))
			SDL_Quit();
	}
}
