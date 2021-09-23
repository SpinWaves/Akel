// This file is a part of Akel
// CREATED : 28/03/2021
// UPDATED : 23/09/2021

#include <Platform/platform.h>

namespace Ak
{
	SDL_DisplayMode DM;

    WindowComponent::WindowComponent() : RendererComponent(_window) {}

	void WindowComponent::onAttach()
	{
		if(_window == nullptr)
			create();
		RendererComponent::onAttach();
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

	void WindowComponent::update()
	{
		RendererComponent::update();
	}

	void WindowComponent::onEvent(Input& input)
	{
		if(input.getInKey(AK_KEY_ESCAPE))
			input.finish();
	}
	void WindowComponent::onQuit()
	{
		RendererComponent::onQuit();
        SDL_FreeSurface(_icon);
        SDL_DestroyWindow(_window);
	}

	// Functions for window settings that use SDL2 functions. They are here to avoid you to link SDL2
	void WindowComponent::setMaxSize(int x, int y)
	{
		SDL_GetCurrentDisplayMode(0, &DM);
		if(x == AK_WINDOW_MAX_SIZE)
			x = DM.w;
		if(y == AK_WINDOW_MAX_SIZE)
			y = DM.h;
		SDL_SetWindowMaximumSize(_window, x, y);
	}
	void WindowComponent::setMinSize(int x, int y)
	{
		SDL_GetCurrentDisplayMode(0, &DM);
		if(x == AK_WINDOW_MAX_SIZE)
			x = DM.w;
		if(y == AK_WINDOW_MAX_SIZE)
			y = DM.h;
		SDL_SetWindowMinimumSize(_window, x, y);
	}
	void WindowComponent::setPos(int x, int y)
	{
		if(x == AK_WINDOW_POS_CENTER)
			x = SDL_WINDOWPOS_CENTERED;
		if(y == AK_WINDOW_POS_CENTER)
			y = SDL_WINDOWPOS_CENTERED;
		SDL_SetWindowPosition(_window, x, y);
	}
	void WindowComponent::setSize(int x, int y)
	{
		SDL_GetCurrentDisplayMode(0, &DM);
		if(x == AK_WINDOW_MAX_SIZE)
			x = DM.w;
		if(y == AK_WINDOW_MAX_SIZE)
			y = DM.h;
		SDL_SetWindowSize(_window, x, y);
	}
	void WindowComponent::setFullscreen(SDL_bool value)
	{
		SDL_SetWindowFullscreen(_window, value);
	}
	void WindowComponent::setMaximize(SDL_bool value)
	{
		if(value == SDL_TRUE)
			SDL_MaximizeWindow(_window);
		else
			SDL_MinimizeWindow(_window);
	}
	void WindowComponent::setBordered(SDL_bool value)
	{
		SDL_SetWindowBordered(_window, value);
	}
	void WindowComponent::setResizable(SDL_bool value)
	{
		SDL_SetWindowResizable(_window, value);
	}
	void WindowComponent::setShow(SDL_bool value)
	{
		if(value)
			SDL_ShowWindow(_window);
		else
			SDL_HideWindow(_window);
	}
	void WindowComponent::setBrightness(float value)
	{
		SDL_SetWindowBrightness(_window, value);
	}
	void WindowComponent::setOpacity(float value)
	{
		SDL_SetWindowOpacity(_window, value);
	}
	void WindowComponent::setTitle(const char* value)
	{
		SDL_SetWindowTitle(_window, value);
	}
	void WindowComponent::setIcon(const char* value)
	{
		_icon = IMG_Load(value);
		SDL_SetWindowIcon(_window, _icon);
	}

    // ================ Getters ================ //
    std::string WindowComponent::getTitle()
    {
        return _title;
    }
    Maths::Vec2<uint16_t> WindowComponent::getPosition()
    {
        return _position;
    }
    Maths::Vec2<uint16_t> WindowComponent::getSize()
    {
		int x, y = 0;
		SDL_GetWindowSize(_window, &x, &y);
		_size.SET(x, y);
        return _size;
    }

    WindowComponent::~WindowComponent(){}
}
