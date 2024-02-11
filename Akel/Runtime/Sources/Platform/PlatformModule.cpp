// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 11/02/2024

#include <Core/Application.h>
#include <Platform/PlatformModule.h>
#include <Core/Logs.h>
#include <Core/Memory/MemoryManager.h>

#if (defined(AK_USE_SDL2) + defined(AK_USE_GLFW)) == 0
	#error "No backend enabled for the system interface (SDL2, GLFW, ...)"
#elif (defined(AK_USE_SDL2) + defined(AK_USE_GLFW)) != 1
	#error "Too much backends enabled for the system interface (SDL2, GLFW, ...)"
#endif

#if defined(AK_USE_SDL2)
	#include <Drivers/SDL2/SDL2Module.h>
	#include <Drivers/SDL2/SDL2Inputs.h>
#elif defined(AK_USE_GLFW)
	#include <Drivers/GLFW/GLFWModule.h>
	#error "GLFW backend not implemented yet"
#endif

namespace Ak
{
	PlatformModule* PlatformModule::s_instance = nullptr;

	PlatformModule::PlatformModule() : Module("PlatformModule")
	{
		if(s_instance != nullptr)
			FatalError("only one instance of PlatformModule can exist at a given time");
		s_instance = this;

		#if defined(AK_USE_SDL2)
			m_backend_inputs = MemAlloc<SDL2Inputs>();
			if(Application::IsInit()) // Should never fail
				Application::Get().LoadEngineModule<SDL2Module>();
		#elif defined(AK_USE_GLFW)
			if(Application::IsInit()) // Should never fail
				Application::Get().LoadEngineModule<GLFWModule>();
		#endif
	}

	void PlatformModule::Update()
	{
		m_backend_inputs->Update();
		if(Application::IsInit()) // Should never fail
		{
			for(auto component : Application::Get())
				component->OnEvent(*m_backend_inputs);
		}
	}

	PlatformModule& PlatformModule::Get()
	{
		Assert(s_instance != nullptr, "PlatformModule has not been instanciated");
		return *s_instance;
	}

	PlatformModule::~PlatformModule()
	{
		MemFree(m_backend_inputs);
		s_instance = nullptr;
	}
}
