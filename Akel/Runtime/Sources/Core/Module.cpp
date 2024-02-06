// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 06/02/2024

#include <Core/Module.h>
#include <Core/Logs.h>

namespace Ak
{
	Module::Module(std::string name) : m_module_name(std::move(name))
	{
		Debug("Starting %...", m_module_name);
	}

	Module::~Module()
	{
		Debug("Shutdown %",  m_module_name);
	}
}
