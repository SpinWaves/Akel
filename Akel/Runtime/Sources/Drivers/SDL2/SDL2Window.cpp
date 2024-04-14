// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/02/2024
// Updated : 14/04/2024

#include "Platform/SI/WindowBackend.h"
#include <Drivers/SDL2/SDL2Window.h>
#include <Core/Logs.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_syswm.h>

namespace Ak
{
	SDL2Window::SDL2Window(std::size_t width, std::size_t height, const std::string& title, WindowStyle style) : SIWindow(width, height, title, style) {}

	void SDL2Window::CreateWindow()
	{
		std::uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI;
		if(m_style & WindowDummy)
			flags = SDL_WINDOW_HIDDEN;
		else
		{
			if(m_style & WindowResizable)
				flags |= SDL_WINDOW_RESIZABLE;
			if(m_style & WindowNoBorders)
				flags |= SDL_WINDOW_BORDERLESS;
			if(m_style & WindowFullscreen)
				flags |= SDL_WINDOW_FULLSCREEN;
			if(m_style & WindowFullscreenDesktop)
				flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_size.x, m_size.y, flags);
		if(!m_window)
			FatalError("SDL2 : cannot create window; %", SDL_GetError());
		DebugLog("SDL2 Window created");
		SDL_GetWindowPosition(m_window, &m_pos.x, &m_pos.y);

		SDL_SysWMinfo info;
		SDL_VERSION(&info.version);
		if(SDL_GetWindowWMInfo(m_window, &info) != SDL_TRUE)
			FatalError("SDL2 : cannot retrieve window informations");
		switch(info.subsystem)
		{
			case SDL_SYSWM_WINDOWS :
			{
				m_backend.backend_in_use = WindowBackendType::WinAPI;
				#ifdef SDL_VIDEO_DRIVER_WINDOWS
					m_backend.win_api.window = info.info.win.window;
				#else
					FatalError("SDL2 : inconsistent informations");
				#endif
				break;
			}
			case SDL_SYSWM_X11 :
			{
				m_backend.backend_in_use = WindowBackendType::X11;
				#ifdef SDL_VIDEO_DRIVER_X11
					m_backend.x11.window = info.info.x11.window;
					m_backend.x11.display = info.info.x11.display;
				#else
					FatalError("SDL2 : inconsistent informations");
				#endif
				break;
			}
			case SDL_SYSWM_COCOA :
			{
				m_backend.backend_in_use = WindowBackendType::Cocoa;
				#ifdef SDL_VIDEO_DRIVER_COCOA
					m_backend.cocoa.window = info.info.cocoa.window;
				#else
					FatalError("SDL2 : inconsistent informations");
				#endif
				break;
			}
			case SDL_SYSWM_WAYLAND :
			{
				m_backend.backend_in_use = WindowBackendType::Wayland;
				#ifdef SDL_VIDEO_DRIVER_WAYLAND
					m_backend.wayland.display = info.info.wl.display;
					m_backend.wayland.surface = info.info.wl.surface;
					m_backend.wayland.shell_surface = info.info.wl.shell_surface;
				#else
					FatalError("SDL2 : inconsistent informations");
				#endif
				break;
			}
			case SDL_SYSWM_ANDROID : break;

			default : FatalError("SDL2 : unsupported windowing system"); break;
		}
	}

	void SDL2Window::UpdateWindowInfos() noexcept
	{
		std::uint32_t bits = SDL_GetWindowFlags(m_window);
		m_is_maximized = bits & SDL_WINDOW_MAXIMIZED;
		m_is_minimized = bits & SDL_WINDOW_MINIMIZED;
		m_is_resizable = bits & SDL_WINDOW_RESIZABLE;
		m_is_fullscreen = bits & SDL_WINDOW_FULLSCREEN;
		m_is_fullscreen_desktop = bits & SDL_WINDOW_FULLSCREEN_DESKTOP;
		if(!m_is_maximized)
			SDL_GetWindowSize(m_window, &m_size.x, &m_size.y);
		SDL_GetWindowPosition(m_window, &m_pos.x, &m_pos.y);
	}

	void SDL2Window::SetPosition(const Vec2i& position) noexcept
	{
		Assert(m_window == nullptr, "Trying to move uninit window");
		SDL_SetWindowPosition(m_window, position.x, position.y);
		m_pos = position;
	}

	void SDL2Window::SetPosition(std::uint32_t posx, std::uint32_t posy) noexcept
	{
		Assert(m_window == nullptr, "Trying to move uninit window");
		SDL_SetWindowPosition(m_window, posx, posy);
		m_pos = Vec2i(posx, posy);
	}

	void SDL2Window::SetSize(const Vec2i& size) noexcept
	{
		Assert(m_window == nullptr, "Trying to set the size of an uninit window");
		SDL_SetWindowSize(m_window, size.x, size.y);
		m_size = size;
	}

	void SDL2Window::SetSize(std::uint32_t sizex, std::uint32_t sizey) noexcept
	{
		Assert(m_window == nullptr, "Trying to set the size of an uninit window");
		SDL_SetWindowSize(m_window, sizex, sizey);
		m_size = Vec2i(sizex, sizey);
	}

	void SDL2Window::SetMaxSize(const Vec2i& size) noexcept
	{
		Assert(m_window == nullptr, "Trying to set the max size of an uninit window");
		SDL_SetWindowMaximumSize(m_window, size.x, size.y);
		m_max_size = size;
	}

	void SDL2Window::SetMaxSize(std::uint32_t sizex, std::uint32_t sizey) noexcept
	{
		Assert(m_window == nullptr, "Trying to set the max size of an uninit window");
		SDL_SetWindowMaximumSize(m_window, sizex, sizey);
		m_max_size = Vec2i(sizex, sizey);
	}

	void SDL2Window::SetMinSize(const Vec2i& size) noexcept
	{
		Assert(m_window == nullptr, "Trying to set the min size of an uninit window");
		SDL_SetWindowMinimumSize(m_window, size.x, size.y);
		m_min_size = size;
	}

	void SDL2Window::SetMinSize(std::uint32_t sizex, std::uint32_t sizey) noexcept
	{
		Assert(m_window == nullptr, "Trying to set the min size of an uninit window");
		SDL_SetWindowMinimumSize(m_window, sizex, sizey);
		m_min_size = Vec2i(sizex, sizey);
	}

	void SDL2Window::SetTitle(const std::string& title)
	{
		Assert(m_window == nullptr, "Trying to change the title of an uninit window");
		SDL_SetWindowTitle(m_window, title.c_str());
		m_title = title;
	}

	SDL2Window::~SDL2Window()
	{
		if(m_window != nullptr)
		{
			SDL_DestroyWindow(m_window);
			m_window = nullptr;
		}
		DebugLog("SDL2 Window destroyed");
	}
}
