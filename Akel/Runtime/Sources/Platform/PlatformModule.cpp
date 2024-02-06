// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 06/02/2024

#include <Platform/PlatformModule.h>
#include <Core/Logs.h>

namespace Ak
{
	PlatformModule* PlatformModule::s_instance = nullptr;

	PlatformModule::PlatformModule() : Module("PlatformModule")
	{
		if(s_instance != nullptr)
			FatalError("only one instance of PlatformModule can exist at a given time");
		s_instance = this;
	}

	PlatformModule& PlatformModule::Get()
	{
		Assert(s_instance != nullptr, "PlatformModule has not been instanciated");
		return *s_instance;
	}

	PlatformModule::~PlatformModule()
	{
		s_instance = nullptr;
	}
}
