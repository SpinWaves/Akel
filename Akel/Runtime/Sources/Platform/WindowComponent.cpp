// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/02/2024
// Updated : 14/04/2024

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
			m_backend_window = MemAlloc<SDL2Window>(width, height, "Akel Window", style);
		#elif defined(AK_GLFW_DRIVER)
			//m_backend_window = MemAlloc<GLFWWindow>(width, height, "Akel Window", style);
		#endif
	}

	WindowComponent::WindowComponent(std::size_t width, std::size_t height, const std::string& title, WindowStyle style) : ComponentBase("__WindowComponent")
	{
		#if defined(AK_SDL2_DRIVER)
			m_backend_window = MemAlloc<SDL2Window>(width, height, title, style);
		#elif defined(AK_GLFW_DRIVER)
			//m_backend_window = MemAlloc<GLFWWindow>(width, height, title, style);
		#endif
	}

	void WindowComponent::OnAttach() noexcept
	{
		m_backend_window->CreateWindow();
	}

	void WindowComponent::OnQuit() noexcept
	{
		MemFree(m_backend_window);
		m_backend_window = nullptr;
	}
}
