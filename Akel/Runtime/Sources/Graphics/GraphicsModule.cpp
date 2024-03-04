// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 23/02/2024

#include <Core/Application.h>
#include <Graphics/GraphicsModule.h>
#include <Core/Logs.h>

namespace Ak
{
	GraphicsModule* GraphicsModule::s_instance = nullptr;

	GraphicsModule::GraphicsModule() : Module("GraphicsModule")
	{
		if(s_instance != nullptr)
			FatalError("only one instance of GraphicsModule can exist at a given time");
		s_instance = this;
	}

	GraphicsModule& GraphicsModule::Get()
	{
		Assert(s_instance != nullptr, "GraphicsModule has not been instanciated");
		return *s_instance;
	}

	void GraphicsModule::LoadDriver()
	{
		#ifdef AK_EMBEDDED_RENDERER_DRIVERS

		#else

		#endif
	}

	GraphicsModule::~GraphicsModule()
	{
		s_instance = nullptr;
	}
}
