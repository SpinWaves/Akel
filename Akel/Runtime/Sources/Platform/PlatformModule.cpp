// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 04/05/2024

#include <Core/Application.h>
#include <Platform/PlatformModule.h>
#include <Core/Logs.h>
#include <Core/Memory/MemoryManager.h>

#if (defined(AK_SDL2_DRIVER) + defined(AK_GLFW_DRIVER)) == 0
	#error "No backend enabled for the system interface (SDL2, GLFW, ...)"
#elif (defined(AK_SDL2_DRIVER) + defined(AK_GLFW_DRIVER)) != 1
	#error "Too much backends enabled for the system interface (SDL2, GLFW, ...)"
#endif

#if defined(AK_SDL2_DRIVER)
	#include <Drivers/SDL2/SDL2Module.h>
	#include <Drivers/SDL2/SDL2Inputs.h>
	#include <Drivers/SDL2/SDL2Window.h>
#elif defined(AK_GLFW_DRIVER)
	#include <Drivers/GLFW/GLFWModule.h>
	#error "GLFW backend is not implemented yet"
#endif

namespace Ak
{
	PlatformModule* PlatformModule::s_instance = nullptr;

	PlatformModule::PlatformModule() : Module("PlatformModule")
	{
		if(s_instance != nullptr)
			FatalError("only one instance of PlatformModule can exist at a given time");
		s_instance = this;

		#if defined(AK_SDL2_DRIVER)
			m_backend_inputs = MemAlloc<SDL2Inputs>();
			if(Application::IsInit()) // Should never fail
				Application::Get().LoadEngineModule<SDL2Module>();
		#elif defined(AK_GLFW_DRIVER)
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

	UniquePtr<SIWindow> PlatformModule::CreateDummyWindow()
	{
		UniquePtr<SIWindow> window;

		#if defined(AK_SDL2_DRIVER)
			window = UniquePtr<SIWindow>(MemAlloc<SDL2Window>(1, 1, "Dummy", WindowDummy));
		#elif defined(AK_GLFW_DRIVER)
			window = UniquePtr<SIWindow>(MemAlloc<GLFWWindow>(1, 1, "Dummy", WindowDummy));
		#endif

		window->CreateWindow();

		return window;
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
