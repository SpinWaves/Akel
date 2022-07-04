// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2021
// Updated : 04/07/2022

#include <Platform/platform.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
	static SDL_DisplayMode DM;

    WindowComponent::WindowComponent() : Component("__window_component")
	{
		size.SET(1280, 750);
		pos.SET(AK_WINDOW_POS_CENTER, AK_WINDOW_POS_CENTER);
		minSize.SET(0, 0);
		maxSize.SET(AK_WINDOW_MAX_SIZE, AK_WINDOW_MAX_SIZE);
	}

	void WindowComponent::onAttach()
	{
		if(_window == nullptr)
			create();
	}

	void WindowComponent::create()
	{
        _flags = SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI;
		
        _window = SDL_CreateWindow(title.c_str(), pos.X, pos.Y, size.X, size.Y, _flags);
        if(!_window)
            messageBox(FATAL_ERROR, "unable to create a window", SDL_GetError());

       	_window_id = SDL_GetWindowID(_window);
       	Input::add_window(this);

        _icon = IMG_Load(std::string(Core::getAssetsDirPath() + "logo.png").c_str());
        SDL_SetWindowIcon(_window, _icon);
	}

	void WindowComponent::fetchSettings()
	{
		SDL_GetCurrentDisplayMode(0, &DM);
		maxSize.X = maxSize.X == AK_WINDOW_MAX_SIZE ? DM.w : maxSize.X;
		maxSize.Y = maxSize.Y == AK_WINDOW_MAX_SIZE ? DM.h : maxSize.Y;

		size.X = size.X == AK_WINDOW_MAX_SIZE ? DM.w : size.X;
		size.Y = size.Y == AK_WINDOW_MAX_SIZE ? DM.h : size.Y;

        _icon = IMG_Load(std::string(Core::getAssetsDirPath() + "logo.png").c_str());
        SDL_SetWindowIcon(_window, _icon);
		SDL_SetWindowTitle(_window, title.c_str());
		SDL_SetWindowPosition(_window, pos.X, pos.Y);
		SDL_SetWindowSize(_window, size.X, size.Y);
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
		Render_Core::get().requireFrameBufferResize();
	}

	void WindowComponent::update()
	{
		SDL_GetWindowPosition(_window, &pos.X, &pos.Y);
		SDL_GetWindowSize(_window, &size.X, &size.Y);
	}

	void WindowComponent::onEvent(Input& input)
	{
		if(input.getInKey(AK_KEY_ESCAPE))
			input.finish();
	}

	void WindowComponent::onQuit()
	{
        SDL_FreeSurface(_icon);
        SDL_DestroyWindow(_window);
	}
}
