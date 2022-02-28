// This file is a part of Akel
// CREATED : 28/03/2021
// UPDATED : 28/02/2022

#include <Platform/platform.h>

namespace Ak
{
	static SDL_DisplayMode DM;

    WindowComponent::WindowComponent() : Component("__window_component") {}

	void WindowComponent::onAttach()
	{
		if(_window == nullptr)
			create();
	}

	void WindowComponent::create()
	{
        _position.SET(0, 0);
        _size.SET(0, 0);

        _flags = SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI;

        _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 506, _flags);
        if(!_window)
            messageBox(FATAL_ERROR, "Unable to create a window", SDL_GetError());

        _icon = IMG_Load(std::string(Core::getAssetsDirPath() + "logo.png").c_str());
        SDL_SetWindowIcon(_window, _icon);
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

	void WindowComponent::setSetting(winsets setting, const char* value)
	{
		switch(setting)
		{
			case winsets::title: SDL_SetWindowTitle(_window, value); break;
			case winsets::icon: _icon = IMG_Load(value); SDL_SetWindowIcon(_window, _icon); break;

			default: Core::log::report(ERROR, "Unable to modify window's parameter"); break;
		}
	}
	void WindowComponent::setSetting(winsets setting, bool value)
	{
		SDL_bool __value = value ? SDL_TRUE : SDL_FALSE;
		switch(setting)
		{
			case winsets::fullscreen: SDL_SetWindowFullscreen(_window, __value); break;
			case winsets::border:     SDL_SetWindowBordered(_window, __value); break;
			case winsets::resizable:  SDL_SetWindowResizable(_window, __value); break;
			case winsets::visible:
			{
				if(value)
					SDL_ShowWindow(_window);
				else
					SDL_HideWindow(_window);
				break;
			}
			case winsets::vsync:  break; // TODO
			case winsets::maximize:
			{
				if(value)
					SDL_MaximizeWindow(_window);
				else
					SDL_MinimizeWindow(_window);
				break;
			}

			default: Core::log::report(ERROR, "Unable to modify window's parameter"); break;
		}
	}
	void WindowComponent::setSetting(winsets setting, float value)
	{
		switch(setting)
		{
			case winsets::brightness: SDL_SetWindowBrightness(_window, value); break;
			case winsets::opacity: SDL_SetWindowOpacity(_window, value); break;

			default: Core::log::report(ERROR, "Unable to modify window's parameter"); break;
		}
	}
	void WindowComponent::setSetting(winsets setting, uint16_t x, uint16_t y)
	{
		switch(setting)
		{
			case winsets::position:
			{
				if(x == AK_WINDOW_POS_CENTER)
					x = SDL_WINDOWPOS_CENTERED;
				if(y == AK_WINDOW_POS_CENTER)
					y = SDL_WINDOWPOS_CENTERED;
				SDL_SetWindowPosition(_window, x, y);
				break;
			}
			case winsets::size:
			{
				SDL_GetCurrentDisplayMode(0, &DM);
				if(x == AK_WINDOW_MAX_SIZE)
					x = DM.w;
				if(y == AK_WINDOW_MAX_SIZE)
					y = DM.h;
				SDL_SetWindowSize(_window, x, y);
				break;
			}
			case winsets::maximumSize:
			{
				SDL_GetCurrentDisplayMode(0, &DM);
				if(x == AK_WINDOW_MAX_SIZE)
					x = DM.w;
				if(y == AK_WINDOW_MAX_SIZE)
					y = DM.h;
				SDL_SetWindowMaximumSize(_window, x, y);
				break;
			}
			case winsets::minimumSize: 
			{
				SDL_GetCurrentDisplayMode(0, &DM);
				if(x == AK_WINDOW_MAX_SIZE)
					x = DM.w;
				if(y == AK_WINDOW_MAX_SIZE)
					y = DM.h;
				SDL_SetWindowMinimumSize(_window, x, y);
				break;
			}

			default: Core::log::report(ERROR, "Unable to modify window's parameter"); break;
		}
	}

    // ================ Getters ================ //
    const Maths::Vec2<uint16_t>& WindowComponent::getSize()
    {
		int x, y = 0;
		SDL_GetWindowSize(_window, &x, &y);
		_size.SET(x, y);
        return _size;
    }

    WindowComponent::~WindowComponent(){}
}
