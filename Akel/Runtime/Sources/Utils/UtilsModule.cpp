// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 08/02/2024

#include <Utils/UtilsModule.h>
#include <Core/Logs.h>

namespace Ak
{
	UtilsModule* UtilsModule::s_instance = nullptr;

	UtilsModule::UtilsModule() : Module("UtilsModule")
	{
		if(s_instance != nullptr)
			FatalError("only one instance of UtilsModule can exist at a given time");
		s_instance = this;
	}

	UtilsModule& UtilsModule::Get()
	{
		Assert(s_instance != nullptr, "UtilsModule has not been instanciated");
		return *s_instance;
	}

	UtilsModule::~UtilsModule()
	{
		s_instance = nullptr;
	}
}
