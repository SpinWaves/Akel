// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 04/03/2024

#include <Core/Module.h>
#include <Core/Logs.h>

namespace Ak
{
	Module::Module(std::string name) : m_module_name(std::move(name))
	{
		DebugLog("Starting %...", m_module_name);
	}

	Module::~Module()
	{
		DebugLog("Shutdown %",  m_module_name);
	}
}
