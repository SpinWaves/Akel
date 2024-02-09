// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/02/2024
// Updated : 09/02/2024

#include <Core/Logs.h>
#include <Platform/SI/Window.h>

namespace Ak
{
	SIWindow::SIWindow(std::size_t width, std::size_t height, const std::string& title, std::uint32_t style) : m_title(title), m_pos(0, 0), m_size(width, height), m_style(style)
	{
		Debug("Window created");
	}

	SIWindow::~SIWindow()
	{
		Debug("Window destroyed");
	}
}
