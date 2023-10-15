// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/06/2021
// Updated : 15/10/2023

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
		{
			Core::log::report(ERROR, "Command Line Args : index out of bounds");
			return nullptr;
		}
		return args[index];
	}

	void Application::init()
	{
		if(_app_check)
			Core::log::report(FATAL_ERROR, "you can only declare one application");
		_app_check = true;
		__main_app = this;
		
		_ticks.init();
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
			Core::log::report(FATAL_ERROR, "SDL error : unable to init all subsystems : %s", SDL_GetError());	
	}

	void Application::run()
	{
		std::thread rendering_thread(&Application::render, this);
		update();
		_stop_rendering = true;
		rendering_thread.join();
	}

	void Application::update()
	{
		float old_timestep = static_cast<float>(SDL_GetTicks64()) / 1000.0f;
		std::vector<std::future<void>> futures;

		while(!_in.isEnded()) // Main update loop
		{
			float curent_timestep = (static_cast<float>(SDL_GetTicks64()) / 1000.0f) - old_timestep;
			old_timestep = static_cast<float>(SDL_GetTicks64()) / 1000.0f;
			_ticks.update();
			if(_ticks.makeUpdate()) // updates
			{
				_in.reset();
				while(SDL_PollEvent(_in.getNativeEvent()))
				{
				//	if(ImGuiComponent::getNumComp())
				//		ImGui_ImplSDL2_ProcessEvent(_in.getNativeEvent());
					_in.update();
				}
				for(auto component : _components)
				{
					futures.emplace_back(std::async(&Component::onEvent, component, std::ref(_in)));
					futures.emplace_back(std::async(&Component::onFixedUpdate, component));
				}
			}
			for(auto component : _components)
				futures.emplace_back(std::async(&Component::onUpdate, component, curent_timestep));
			for(auto& future : futures)
				future.wait();
			futures.clear();
		}
	}

	void Application::render()
	{
		std::unordered_map<RendererComponent*, void*> renderers;
		for(auto comp : _components)
		{
			if(comp->getName().compare(0, comp->getName().length() - 1, "__renderer_component") == 0)
				renderers[static_cast<RendererComponent*>(comp)] = nullptr;
		/*	else if(comp->getName() == "__imgui_component")
			{
				ImGuiComponent* imgui = static_cast<ImGuiComponent*>(comp);
				renderers[imgui->_renderer] = imgui;
			}*/
		}
		if(renderers.empty())
			return;

		while(!_stop_rendering) // Main rendering loop
		{
			for(auto& renderer : renderers)
			{
				bool res = renderer.first->beginFrame();
			//	if(renderer.second != nullptr)
			//		renderer.second->beginFrame(res);
			}
			for(auto component : _components)
				component->onRender();
			for(auto& renderer : renderers)
			{
			//	if(renderer.second != nullptr)
			//		renderer.second->renderFrame();
				renderer.first->endFrame();
			}
		}
	}

	void Application::destroy()
	{
		// Renderers and ImGui needs to be destroyed after other components to avoid leaks or bugs
		std::vector<RendererComponent*> renderers;
		//std::vector<ImGuiComponent*> imguis;
		for(auto comp : _components)
		{
			if(comp->getName() == "__renderer_component")
				renderers.push_back(static_cast<RendererComponent*>(comp));
			else
				comp->onQuit();
		//	else if(comp->getName() == "__imgui_component")
		//		imguis.push_back(static_cast<ImGuiComponent*>(comp));
		}
	//	for(auto comp : imguis)
	//		comp->onQuit();
		for(auto comp : renderers)
			comp->onQuit();
		ComponentStack::destroy();
		_app_check = false;
		SDL_Quit();
	}

	void Application::end()
	{
		_in.finish();
	}
}
