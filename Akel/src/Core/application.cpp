// This file is a part of Akel
// CREATED : 10/06/2021
// UPDATED : 28/02/2022

#include <Core/core.h>
#include <Utils/utils.h>
#include <Platform/input.h>
#include <Modules/ImGui/imgui_component.h>
#include <Utils/utils.h>

namespace Ak
{
	Application::Application(const char* name) : ComponentStack(), _in(), _fps()
	{
		_name = name;
		_fps.init();
		if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
			Core::log::report(FATAL_ERROR, std::string("SDL error : unable to init all subsystems : ") + SDL_GetError());
	}

	void Application::run()
	{
		ImGuiComponent imgui;
		while(!_in.isEnded()) // Main loop
		{
			_fps.update();
			// separation between updates and rendering
			if(_fps.make_update()) // updates
			{
				while(SDL_PollEvent(_in.getNativeEvent()))
				{
					_in.update();
					for(auto elem : _components)
						elem->onEvent(_in);
				}
				for(auto elem : _components)
					elem->update();
			}
			else // rendering
			{
				for(auto elem : _components)
				{
					elem->onRender();
					if(ImGuiComponent::getNumComp() != 0)
					{	
						imgui.begin();
							elem->onImGuiRender();
						imgui.end();
					}
				}
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
