// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

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
