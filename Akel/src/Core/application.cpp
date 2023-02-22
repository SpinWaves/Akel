// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/06/2021
// Updated : 22/02/2023

#include <Core/core.h>
#include <Utils/utils.h>
#include <Modules/ImGui/imgui_component.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
	static Application* __main_app = nullptr;

	ComponentStack* getMainAppComponentStack()
	{
		return static_cast<ComponentStack*>(__main_app);
	}

	const char* CommandLineArgs::operator[](int index) const noexcept
	{
		if(index >= count)
			Core::log::report(FATAL_ERROR, "Command Line Args : index out of bounds");
		return args[index];
	}

	Application::Application() : ComponentStack(), non_copyable(), _in(), _fps()
	{
		if(_app_check)
			Core::log::report(FATAL_ERROR, "you can only declare one application");
		_app_check = true;
		__main_app = this;
		
		_fps.init();
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
			Core::log::report(FATAL_ERROR, "SDL error : unable to init all subsystems : %s", SDL_GetError());	
	}

	void Application::run()
	{
		std::vector<RendererComponent*> renderers;
		std::vector<ImGuiComponent*> imguis;
		for(auto comp : _components)
		{
			if(std::strcmp(comp->getName(), "__renderer_component") == 0)
				renderers.push_back(static_cast<RendererComponent*>(comp));
			if(std::strcmp(comp->getName(), "__imgui_component") == 0)
				imguis.push_back(static_cast<ImGuiComponent*>(comp));
		}

		while(!_in.isEnded()) // Main loop
		{
			_fps.update();
			// separation between updates and rendering

			if(_fps.make_update()) // updates
			{
				_in.reset();
				while(SDL_PollEvent(_in.getNativeEvent()))
				{
					if(ImGuiComponent::getNumComp())
					{
						for(auto component : _components)
							component->onImGuiEvent(_in);
					}
					_in.update();
				}
				for(auto component : _components)
				{
					component->onEvent(_in);
					component->update();
				}
			}
			
			// rendering
			for(auto renderer : renderers)
				renderer->beginFrame();
			for(auto component : _components)
				component->onRender();
			if(ImGuiComponent::getNumComp())
			{
				for(auto imgui : imguis)
				{
					imgui->_renderer->getActiveCmdBuffer().beginRecord();
					imgui->_renderer->getRenderPass().begin();
				}
				ImGui_ImplVulkan_NewFrame();
				ImGui_ImplSDL2_NewFrame();
				ImGui::NewFrame();

				for(auto component : _components)
					component->onImGuiRender();

				ImGui::Render();
				for(auto imgui : imguis)
				{
					imgui->renderFrame();
					imgui->_renderer->getRenderPass().end();
					imgui->_renderer->getActiveCmdBuffer().endRecord();
				}
			}
			for(auto renderer : renderers)
				renderer->endFrame();
		}
	}

	void Application::destroy()
	{
		for(auto component : _components)
			component->onQuit();
		_app_check = false;
		SDL_Quit();
	}

	void Application::end()
	{
		_in.finish();
	}

	Application::~Application()
	{
		if(_app_check)
			destroy();
	}
}
