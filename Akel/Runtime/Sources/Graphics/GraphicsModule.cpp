// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 12/02/2024

#include <Core/Application.h>
#include <Graphics/GraphicsModule.h>
#include <Core/Logs.h>

namespace Ak
{
	GraphicsModule* GraphicsModule::s_instance = nullptr;

	GraphicsModule::GraphicsModule(RenderBackend backend) : Module("GraphicsModule")
	{
		if(s_instance != nullptr)
			FatalError("only one instance of GraphicsModule can exist at a given time");
		s_instance = this;

		if(backend == RenderBackend::Vulkan)
		{

		}
	}

	GraphicsModule& GraphicsModule::Get()
	{
		Assert(s_instance != nullptr, "GraphicsModule has not been instanciated");
		return *s_instance;
	}

	GraphicsModule::~GraphicsModule()
	{
		s_instance = nullptr;
	}
}
