// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Platform/WindowComponent.h>
#include <Core/Memory/MemoryManager.h>

#if defined(AK_SDL2_DRIVER)
	#include <Drivers/SDL2/SDL2Window.h>
#elif defined(AK_GLFW_DRIVER)
	#error "GLFW backend not implemented yet"
#endif

namespace Ak
{
	WindowComponent::WindowComponent(std::size_t width, std::size_t height, WindowStyle style) : ComponentBase("__WindowComponent")
	{
		#if defined(AK_SDL2_DRIVER)
			p_backend_window = MakeUnique<SDL2Window>(width, height, "Akel Window", style);
		#elif defined(AK_GLFW_DRIVER)
			//m_backend_window = MakeUnique<GLFWWindow>(width, height, "Akel Window", style);
		#endif
	}

	WindowComponent::WindowComponent(std::size_t width, std::size_t height, const std::string& title, WindowStyle style) : ComponentBase("__WindowComponent")
	{
		#if defined(AK_SDL2_DRIVER)
			p_backend_window = MakeUnique<SDL2Window>(width, height, title, style);
		#elif defined(AK_GLFW_DRIVER)
			//m_backend_window = MakeUnique<GLFWWindow>(width, height, title, style);
		#endif
	}

	void WindowComponent::OnAttach() noexcept
	{
		p_backend_window->CreateWindow();
	}

	void WindowComponent::OnQuit() noexcept
	{
		p_backend_window.Reset();
	}
}
