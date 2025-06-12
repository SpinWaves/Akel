// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Core/CoreModule.h>
#include <Core/Logs.h>
#include <Config.h>

namespace Ak
{
	namespace Core::Memory::Internal
	{
		void Init();
		void Shutdown();
	}

	CoreModule* CoreModule::s_instance = nullptr;

	CoreModule::CoreModule() : Module("CoreModule")
	{
		if(s_instance != nullptr)
			FatalError("only one instance of CoreModule can exist at a given time");
		s_instance = this;
		Core::Memory::Internal::Init();
		m_ticks.Init();
	}

	std::string CoreModule::GetEngineModuleVersion()
	{
		return AKEL_VERSION;
	}

	CoreModule& CoreModule::Get()
	{
		Verify(s_instance != nullptr, "CoreModule has not been instanciated");
		return *s_instance;
	}

	CoreModule::~CoreModule()
	{
		Module::~Module();
		Core::Memory::Internal::Shutdown();
		s_instance = nullptr;
	}
}
