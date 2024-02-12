// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/02/2024
// Updated : 12/02/2024

#include <Core/Logs.h>
#include <Platform/SI/Window.h>

namespace Ak
{
	SIWindow::SIWindow(std::size_t width, std::size_t height, const std::string& title, WindowStyle style) : m_title(title), m_pos(0, 0), m_size(width, height), m_style(style)
	{
		Debug("Window created");
	}

	SIWindow::~SIWindow()
	{
		Debug("Window destroyed");
	}
}
