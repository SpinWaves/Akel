// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/06/2021
// Updated : 02/03/2022

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
			Core::log::report(FATAL_ERROR, "SDL error : unable to init all subsystems : %s", SDL_GetError());
	}

	void Application::run()
	{
		ImGuiComponent __imgui;
		while(!_in.isEnded()) // Main loop
		{
			_fps.update();
			// separation between updates and rendering
			if(_fps.make_update()) // updates
			{
				while(SDL_PollEvent(_in.getNativeEvent()))
				{
					_in.update();
					for(auto component : _components)
						component->onEvent(_in);
				}
				for(auto component : _components)
					component->update();
			}
			
			// rendering
			if(ImGuiComponent::getNumComp() != 0) // __imgui doesn't modify it because we don't attach it
			{
				__imgui.begin();
				for(auto component : _components)
				{
					component->onRender();
					component->onImGuiRender();
				}
				__imgui.end();
			}
			else
			{
				for(auto component : _components)
					component->onRender();
			}
		}

		for(auto component : _components)
			component->onQuit();
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
