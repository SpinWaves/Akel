// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Platform/SI/Window.h>
#include <Core/Logs.h>

namespace Ak
{
	SIWindow::SIWindow(std::size_t width, std::size_t height, const std::string& title, WindowStyle style) : m_title(title), m_pos(0, 0), m_size(width, height), m_style(style)
	{
		DebugLog("Window created");
	}

	SIWindow::~SIWindow()
	{
		DebugLog("Window destroyed");
	}
}
