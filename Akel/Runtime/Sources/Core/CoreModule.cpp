// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/02/2024
// Updated : 06/02/2024

#include <Core/CoreModule.h>
#include <Core/Logs.h>

namespace Ak
{
	CoreModule* CoreModule::s_instance = nullptr;

	CoreModule::CoreModule() : Module("CoreModule")
	{
		if(s_instance != nullptr)
			FatalError("only one instance of CoreModule can exist at a given time");
		s_instance = this;
	}

	CoreModule& CoreModule::Get()
	{
		Assert(s_instance != nullptr, "CoreModule has not been instanciated");
		return *s_instance;
	}

	CoreModule::~CoreModule()
	{
		s_instance = nullptr;
	}
}
