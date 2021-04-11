// This file is a part of AtlasEngine
// CREATED : 28/03/2021
// UPDATED : 05/04/2021

#include <Platform/window.h>

namespace AE
{
    Window::Window() : Context(), Instance()
    {}

    void Window::create(std::string title, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t flags)
    {
        _title = title;
        _posx = x;
        _posy = y;
        _width = width;
        _height = height;
        _flags = flags;
 
        _window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
        _icon = IMG_Load(std::string(Core::getAssetsDirPath() + "logo.png").c_str());
        SDL_SetWindowIcon(_window, _icon);
    }

    // ================ Setters ================ //

    void Window::setTitle(std::string title)
    {
        _title = std::move(title);
    }
    void Window::setFlags(uint32_t flags)
    {
        _flags = flags;
    }
    void Window::setPosition(uint16_t x, uint16_t y)
    {
        _posx = x;
        _posy = y;
    }
    void Window::setSize(uint16_t width, uint16_t height)
    {
        _width = width;
        _height = height;
    }
    void Window::setIcon(SDL_Surface* image)
    {
        _icon = image;
        SDL_SetWindowIcon(_window, _icon);
    }
    void Window::setIcon(std::string imagePath)
    {
        _icon = IMG_Load(imagePath.c_str());
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
    uint16_t Window::getPositionX()
    {
        return _posx;
    }
    uint16_t Window::getPositionY()
    {
        return _posy;
    }
    uint16_t Window::getSizeW()
    {
        return _width;
    }
    uint16_t Window::getSizeH()
    {
        return _height;
    }


    void Window::initWindowRenderer()
    {
        if(_flags & AE_WINDOW_OPENGL)
            Context::init(_window);
        if(_flags & AE_WINDOW_VULKAN)
            Instance::init(_window);
    }
    void Window::update()
    {
        if(_flags & AE_WINDOW_OPENGL)
            Context::SwapBuffers();
    }


    void Window::destroy()
    {
        if(Context::isCreated())
            Context::destroy();
        Instance::destroy();
        SDL_DestroyWindow(_window);
    }

    Window::~Window()
    {
        SDL_FreeSurface(_icon);
    }
}
