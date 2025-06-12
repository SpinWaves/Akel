// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Platform/PlatformModule.h>
#include <Core/CoreModule.h>
#include <Core/Application.h>
#include <Config.h>

namespace Ak
{
	Application* Application::s_instance = nullptr;

	Application::Application(const EngineConfig& config) : m_engine_config(config), m_engine_version(AKEL_VERSION)
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
