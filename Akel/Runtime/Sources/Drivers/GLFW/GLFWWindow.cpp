// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2024
// Updated : 04/03/2024

#include <Drivers/GLFW/GLFWWindow.h>
#include <Platform/Enums.h>
#include <Core/Logs.h>

namespace Ak
{
	GLFWWindow::GLFWWindow(std::size_t width, std::size_t height, const std::string& title, WindowStyle style) : SIWindow(width, height, title, style) {}

	void GLFWWindow::CreateWindow()
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if(m_window)
			DebugLog("GLFW Window created");
	}

	void GLFWWindow::UpdateWindowInfos() noexcept
	{
	}

	void GLFWWindow::SetPosition(const Vec2i& position) noexcept
	{
		Assert(m_window == nullptr, "Trying to move uninit window");
	}

	void GLFWWindow::SetPosition(std::uint32_t posx, std::uint32_t posy) noexcept
	{
		Assert(m_window == nullptr, "Trying to move uninit window");
	}

	void GLFWWindow::SetSize(const Vec2i& size) noexcept
	{
		Assert(m_window == nullptr, "Trying to set the size of an uninit window");
	}

	void GLFWWindow::SetSize(std::uint32_t sizex, std::uint32_t sizey) noexcept
	{
		Assert(m_window == nullptr, "Trying to set the size of an uninit window");
	}

	void GLFWWindow::SetMaxSize(const Vec2i& size) noexcept
	{
		Assert(m_window == nullptr, "Trying to set the max size of an uninit window");
	}

	void GLFWWindow::SetMaxSize(std::uint32_t sizex, std::uint32_t sizey) noexcept
	{
		Assert(m_window == nullptr, "Trying to set the max size of an uninit window");
	}

	void GLFWWindow::SetMinSize(const Vec2i& size) noexcept
	{
		Assert(m_window == nullptr, "Trying to set the min size of an uninit window");
	}

	void GLFWWindow::SetMinSize(std::uint32_t sizex, std::uint32_t sizey) noexcept
	{
		Assert(m_window == nullptr, "Trying to set the min size of an uninit window");
	}

	void GLFWWindow::SetTitle(const std::string& title)
	{
		Assert(m_window == nullptr, "Trying to change the title of an uninit window");
	}

	GLFWWindow::~GLFWWindow()
	{
		if(m_window != nullptr)
		{
			glfwDestroyWindow(m_window);
			m_window = nullptr;
		}
		DebugLog("GLFW Window destroyed");
	}
}
