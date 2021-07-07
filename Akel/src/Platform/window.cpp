// This file is a part of Akel
// CREATED : 28/03/2021
// UPDATED : 07/07/2021

#include <Platform/platform.h>

namespace Ak
{
	SDL_DisplayMode DM;

    Window::Window() : Instance(), Component("__window") {}
	
	void Window::onAttach()
	{
		if(_window == nullptr)
			create();
        Instance::init(_window, "vert.spv", "frag.spv");
	}

	void Window::create()
	{
        _position.SET(0, 0);
        _size.SET(0, 0);

        _flags = SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI;
 
        _window = SDL_CreateWindow(_title.c_str(), 0, 0, 0, 0, _flags);
        if(!_window)
            messageBox(FATAL_ERROR, "Unable to create a window", SDL_GetError());

        _icon = IMG_Load(std::string(Core::getAssetsDirPath() + "logo.png").c_str());
        SDL_SetWindowIcon(_window, _icon);
	}

	void Window::update()
	{
		render();
	}

	void Window::onEvent(Input& input)
	{
		if(input.getInKey(AK_KEY_ESCAPE))
			input.finish();
	}
	void Window::onQuit()
	{
        Instance::cleanup();
        SDL_FreeSurface(_icon);
        SDL_DestroyWindow(_window);
	}

	// Functions for window settings that use SDL2 functions. They are here to avoid you to link SDL2
	void Window::setMaxSize(int x, int y)
	{
		SDL_GetCurrentDisplayMode(0, &DM);
		if(x == AK_WINDOW_MAX_SIZE)
			x = DM.w;
		if(y == AK_WINDOW_MAX_SIZE)
			y = DM.h;
		SDL_SetWindowMaximumSize(_window, x, y);
	}
	void Window::setMinSize(int x, int y)
	{
		SDL_GetCurrentDisplayMode(0, &DM);
		if(x == AK_WINDOW_MAX_SIZE)
			x = DM.w;
		if(y == AK_WINDOW_MAX_SIZE)
			y = DM.h;
		SDL_SetWindowMinimumSize(_window, x, y);
	}
	void Window::setPos(int x, int y)
	{
		if(x == AK_WINDOW_POS_CENTER)
			x = SDL_WINDOWPOS_CENTERED;
		if(y == AK_WINDOW_POS_CENTER)
			y = SDL_WINDOWPOS_CENTERED;
		SDL_SetWindowPosition(_window, x, y);
	}
	void Window::setSize(int x, int y)
	{
		SDL_GetCurrentDisplayMode(0, &DM);
		if(x == AK_WINDOW_MAX_SIZE)
			x = DM.w;
		if(y == AK_WINDOW_MAX_SIZE)
			y = DM.h;
		SDL_SetWindowSize(_window, x, y);
	}
	void Window::setFullscreen(SDL_bool value)
	{
		SDL_SetWindowFullscreen(_window, value);
	}
	void Window::setBordered(SDL_bool value)
	{
		SDL_SetWindowBordered(_window, value);
	}
	void Window::setResizable(SDL_bool value)
	{
		SDL_SetWindowResizable(_window, value);
	}
	void Window::setShow(SDL_bool value)
	{
		if(value)
			SDL_ShowWindow(_window);
		else
			SDL_HideWindow(_window);
	}
	void Window::setBrightness(float value)
	{
		SDL_SetWindowBrightness(_window, value);
	}
	void Window::setOpacity(float value)
	{
		SDL_SetWindowOpacity(_window, value);
	}
	void Window::setTitle(const char* value)
	{
		SDL_SetWindowTitle(_window, value);
	}
	void Window::setIcon(const char* value)
	{
		_icon = IMG_Load(value);
		SDL_SetWindowIcon(_window, _icon);
	}

    // ================ Getters ================ //
    std::string Window::getTitle()
    {
        return _title;
    }
    Maths::Vec2<uint16_t> Window::getPosition()
    {
        return _position;
    }
    Maths::Vec2<uint16_t> Window::getSize()
    {
        return _size;
    }

    Window::~Window(){}
}

