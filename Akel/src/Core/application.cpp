// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/06/2021
// Updated : 05/07/2022

#include <Core/core.h>
#include <Utils/utils.h>
#include <Modules/ImGui/imgui_component.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
	Application::Application(const char* name) : ComponentStack(), non_copyable(), _in(), _fps()
	{
		if(_app_check)
			Core::log::report(FATAL_ERROR, "you can only declare one application");
		_app_check = true;
		
		_name = name;
		_fps.init();
//		if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
//			Core::log::report(FATAL_ERROR, "SDL error : unable to init all subsystems : %s", SDL_GetError());
	}

	void Application::run()
	{
		while(!_in.isEnded()) // Main loop
		{
			_fps.update();
			// separation between updates and rendering

			if(_fps.make_update()) // updates
			{
				_in.reset();
				while(SDL_PollEvent(_in.getNativeEvent()))
				{
					_in.update();
					for(auto component : _components)
					{
						if(ImGuiComponent::getNumComp() != 0)
							component->onImGuiEvent(_in);
					}
				}
				for(auto component : _components)
				{
					component->onEvent(_in);
					component->update();
				}
			}
			
			if(Render_Core::get().beginFrame())
			{
				// rendering
				if(ImGuiComponent::getNumComp() != 0)
				{
					ImGui_ImplVulkan_NewFrame();
					ImGui_ImplSDL2_NewFrame();
					ImGui::NewFrame();

					for(auto component : _components)
					{
						component->onRender();
						component->onImGuiRender();
					}

					ImGui::Render();
					ImDrawData* draw_data = ImGui::GetDrawData();
					if(draw_data->DisplaySize.x >= 0.0f && draw_data->DisplaySize.y >= 0.0f)
						ImGui_ImplVulkan_RenderDrawData(draw_data, Render_Core::get().getActiveCmdBuffer().get());
				}
				else
				{
					for(auto component : _components)
						component->onRender();
				}
				Render_Core::get().endFrame();
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
