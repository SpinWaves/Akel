// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/02/2024
// Updated : 06/02/2024

#include <Core/Application.h>

namespace Ak
{
	void Application::ShutdownAllEngineModules()
	{
		for(auto it = m_modules.rbegin(); it != m_modules.rend(); ++it)
			delete *it;
		m_modules.clear();
	}
}
