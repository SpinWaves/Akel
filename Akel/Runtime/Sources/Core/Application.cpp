// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/02/2024
// Updated : 10/04/2024

#include <Platform/PlatformModule.h>
#include <Core/CoreModule.h>
#include <Core/Application.h>

namespace Ak
{
	Application* Application::s_instance = nullptr;

	Application::Application(const EngineConfig& config) : m_engine_config(config)
	{
		s_instance = this;
		LoadEngineModule<CoreModule>();
	}

	void Application::Run()
	{
		m_running = true;

		// Main update loop
		while(m_running)
		{
			auto& ticks = CoreModule::Get().GetTicksReference();
			ticks.Update();

			// Fixed updates
			if(ticks.ShouldMakeUpdate())
			{
				for(auto module : m_modules)
					module->Update();
				for(auto component : m_components)
					component->OnFixedUpdate();
			}
		}

		// Cleanup
		for(auto comp : m_components)
			comp->OnQuit();
		ComponentStack::Destroy();
	}

	Application& Application::Get()
	{
		Assert(s_instance != nullptr, "Application has not been instanciated");
		return *s_instance;
	}

	void Application::ShutdownAllEngineModules()
	{
		for(auto it = m_modules.rbegin(); it != m_modules.rend(); ++it)
			delete *it;
		m_modules.clear();
	}

	Application::~Application()
	{
		s_instance = nullptr;
	}
}
