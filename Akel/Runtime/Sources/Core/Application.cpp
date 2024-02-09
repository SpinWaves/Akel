// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/02/2024
// Updated : 09/02/2024

#include <Core/CoreModule.h>
#include <Core/Application.h>

namespace Ak
{
	Application::Application()
	{
		LoadEngineModule<CoreModule>();
	}

	void Application::Run()
	{
		// Cleanup
		for(auto comp : m_components)
			comp->OnQuit();
		ComponentStack::Destroy();
	}

	void Application::ShutdownAllEngineModules()
	{
		for(auto it = m_modules.rbegin(); it != m_modules.rend(); ++it)
			delete *it;
		m_modules.clear();
	}
}
