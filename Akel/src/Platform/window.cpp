// This file is a part of Akel
// CREATED : 28/03/2021
// UPDATED : 13/06/2021

#include <Platform/platform.h>

namespace Ak
{
    Window::Window() : Instance() {}

    void Window::create(std::string title, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
    {
        _title = title;
        _position.SET(x, y);
        _size.SET(width, height);
        SDL_Init(SDL_INIT_VIDEO);
		atexit(exit);

        _flags = SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN;
 
        _window = SDL_CreateWindow(title.c_str(), x, y, width, height, _flags);
        if(!_window)
            messageBox(FATAL_ERROR, "Unable to create a window", SDL_GetError());

        _icon = IMG_Load(std::string(Core::getAssetsDirPath() + "logo.png").c_str());
        SDL_SetWindowIcon(_window, _icon);
	}
	// Functions for window settings that use SDL2 functions. They are here to avoid you to link SDL2
	void Window::setMaxSize(int x, int y)
	{
		SDL_SetWindowMaximumSize(_window, x, y);
	}
	void Window::setMinSize(int x, int y)
	{
		SDL_SetWindowMinimumSize(_window, x, y);
	}
	void Window::setPos(int x, int y)
	{
		SDL_SetWindowPosition(_window, x, y);
	}
	void Window::setSize(int x, int y)
	{
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
    uint32_t Window::getFlags()
    {
        return _flags;
    }
    Maths::Vec2<uint16_t> Window::getPosition()
    {
        return _position;
    }
    Maths::Vec2<uint16_t> Window::getSize()
    {
        return _size;
    }

    void Window::initWindowRenderer(const char* vert, const char* frag)
    {
        Instance::init(_window, vert, frag);
    }

    void Window::destroy()
    {
        SDL_FreeSurface(_icon);
        Instance::cleanup();
        SDL_DestroyWindow(_window);
    }

    Window::~Window(){}
}

