// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2021
// Updated : 15/05/2023

#include <Platform/platform.h>
#include <Renderer/rendererComponent.h>
#include <Utils/logo_ico.h>

namespace Ak
{
	static SDL_DisplayMode DM;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		static const uint32_t rmask = 0xff000000;
		static const uint32_t gmask = 0x00ff0000;
		static const uint32_t bmask = 0x0000ff00;
		static const uint32_t amask = 0x000000ff;
	#else
		static const uint32_t rmask = 0x000000ff;
		static const uint32_t gmask = 0x0000ff00;
		static const uint32_t bmask = 0x00ff0000;
		static const uint32_t amask = 0xff000000;
	#endif

    WindowComponent::WindowComponent() : Component("__window_component")
	{
		size.set(1280, 750);
		pos.set(AK_WINDOW_POS_CENTER, AK_WINDOW_POS_CENTER);
		minSize.set(0, 0);
		maxSize.set(AK_WINDOW_MAX_SIZE, AK_WINDOW_MAX_SIZE);
	}

	void WindowComponent::onAttach()
	{
		if(_window == nullptr)
			create();
		getMainAppProjectFile().archive()["__window_component"] = true;
	}

	void WindowComponent::create()
	{
        _flags = SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI;
		
        _window = SDL_CreateWindow(title.c_str(), pos.X, pos.Y, size.X, size.Y, _flags);
        if(!_window)
            messageBox(FATAL_ERROR, "unable to create a window", SDL_GetError());

       	_window_id = SDL_GetWindowID(_window);
       	Input::add_window(this);

		_icon = SDL_CreateRGBSurfaceFrom(static_cast<void*>(logo_icon_data), logo_size, logo_size, 32, 4 * logo_size, rmask, gmask, bmask, amask);
        SDL_SetWindowIcon(_window, _icon);
	}

	void WindowComponent::fetchSettings()
	{
		SDL_GetCurrentDisplayMode(0, &DM);
		maxSize.X = maxSize.X == AK_WINDOW_MAX_SIZE ? DM.w : maxSize.X;
		maxSize.Y = maxSize.Y == AK_WINDOW_MAX_SIZE ? DM.h : maxSize.Y;

		size.X = size.X == AK_WINDOW_MAX_SIZE ? DM.w : size.X;
		size.Y = size.Y == AK_WINDOW_MAX_SIZE ? DM.h : size.Y;
/*
		if(icon == "default_Akel_icon")
			_icon = SDL_CreateRGBSurfaceFrom(static_cast<void*>(logo_icon_data), logo_size, logo_size, 32, 4 * logo_size, rmask, gmask, bmask, amask);
		else
			_icon = IMG_Load(icon.c_str());
*/
		SDL_SetWindowIcon(_window, _icon);
		SDL_SetWindowTitle(_window, title.c_str());
		SDL_SetWindowSize(_window, size.X, size.Y);
		SDL_SetWindowPosition(_window, pos.X, pos.Y);
		SDL_SetWindowMinimumSize(_window, minSize.X, minSize.Y);
		SDL_SetWindowMaximumSize(_window, maxSize.X, maxSize.Y);
		SDL_SetWindowBrightness(_window, brightness);
		SDL_SetWindowOpacity(_window, opacity);
		SDL_SetWindowFullscreen(_window, fullscreen ? SDL_TRUE : SDL_FALSE);
		SDL_SetWindowResizable(_window, resizable ? SDL_TRUE : SDL_FALSE);
		SDL_SetWindowBordered(_window, border ? SDL_TRUE : SDL_FALSE);
		if(maximize)
		{
			SDL_MaximizeWindow(_window);
			minimize = false;
		}
		if(minimize)
		{
			SDL_MinimizeWindow(_window);
			maximize = false;
		}
		visible ? SDL_ShowWindow(_window) : SDL_HideWindow(_window);
		if(_renderer != nullptr)
			_renderer->requireFrameBufferResize();

		getMainAppProjectFile().archive()["window_component"]["title"] = title;
		getMainAppProjectFile().archive()["window_component"]["icon"] = icon;
		getMainAppProjectFile().archive()["window_component"]["size"]["x"] = size.X;
		getMainAppProjectFile().archive()["window_component"]["size"]["y"] = size.Y;
		getMainAppProjectFile().archive()["window_component"]["pos"]["x"] = pos.X;
		getMainAppProjectFile().archive()["window_component"]["pos"]["y"] = pos.Y;
		getMainAppProjectFile().archive()["window_component"]["minSize"]["x"] = minSize.X;
		getMainAppProjectFile().archive()["window_component"]["minSize"]["y"] = minSize.Y;
		getMainAppProjectFile().archive()["window_component"]["maxSize"]["x"] = maxSize.X;
		getMainAppProjectFile().archive()["window_component"]["maxSize"]["y"] = maxSize.Y;
		getMainAppProjectFile().archive()["window_component"]["brightnesss"] = brightness;
		getMainAppProjectFile().archive()["window_component"]["opacity"] = opacity;
		getMainAppProjectFile().archive()["window_component"]["fullscreen"] = fullscreen;
		getMainAppProjectFile().archive()["window_component"]["border"] = border;
		getMainAppProjectFile().archive()["window_component"]["resizable"] = resizable;
		getMainAppProjectFile().archive()["window_component"]["visible"] = visible;
		getMainAppProjectFile().archive()["window_component"]["vsync"] = vsync;
		getMainAppProjectFile().archive()["window_component"]["maximize"] = maximize;
		getMainAppProjectFile().archive()["window_component"]["minimize"] = minimize;
	}

	void WindowComponent::update()
	{
		if(_window == nullptr)
			return;
		SDL_GetWindowPosition(_window, &pos.X, &pos.Y);
		SDL_GetWindowSize(_window, &size.X, &size.Y);
	}

	void WindowComponent::onQuit()
	{
		if(_window != nullptr)
		{
			SDL_FreeSurface(_icon);
			SDL_DestroyWindow(_window);
			_window = nullptr;
		}
		fetchSettings();
	}
}
