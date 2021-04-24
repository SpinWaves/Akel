// This file is a part of AtlasEngine
// CREATED : 28/03/2021
// UPDATED : 24/04/2021

#include <Platform/platform.h>

namespace AE
{
    Window::Window() : Context(), Instance() {}

    void Window::create(std::string title, uint16_t x, uint16_t y, uint16_t width, uint16_t height, windowType type)
    {
        _title = title;
        _position.SET(x, y);
        _size.SET(width, height);

        switch(type)
        {
            case AE_WINDOW_OPENGL: _flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL; break;
            case AE_WINDOW_VULKAN: _flags = SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN; break;
            
            case AE_WINDOW_POP_UP:
            {
                #ifdef _WIN32
                    _flags = SDL_WINDOW_SHOWN | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_BORDERLESS; // Because windows sucks and need it
                #else
                    _flags = SDL_WINDOW_SHOWN | SDL_WINDOW_POPUP_MENU;
                #endif
                break;
            }
            
            case AE_WINDOW_AUTO_TYPE:
            {
                if(Core::isVulkanSupported())
                    _flags = SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN;
                else
                    _flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
                break;
            }

            default: messageBox(FATAL_ERROR, "Unable to create a window", "Bad type"); break;
        }
 
        _window = SDL_CreateWindow(title.c_str(), x, y, width, height, _flags);
        if(!_window)
            messageBox(FATAL_ERROR, "Unable to create a window", SDL_GetError());

        _icon = IMG_Load(std::string(Core::getAssetsDirPath() + "logo.png").c_str());
        SDL_SetWindowIcon(_window, _icon);
    }

    // ================ Setters ================ //
    void Window::setSetting(windowSetting setting, const char* value)
    {
        switch(setting)
        {
            case title: SDL_SetWindowTitle(_window, value); break;
            case icon: _icon = IMG_Load(value); SDL_SetWindowIcon(_window, _icon); break;

            default: messageBox(ERROR, "Unable to modify window's parameter", "No such setting"); break;
        }
    }
    void Window::setSetting(windowSetting setting, bool value)
    {
        SDL_bool pass;
        if(value) pass = SDL_TRUE;
        else      pass = SDL_FALSE;

        switch(setting)
        {
            case fullscreen: SDL_SetWindowFullscreen(_window, pass); break;
            case border:     SDL_SetWindowBordered(_window, pass); break; 
            case resizable:  SDL_SetWindowResizable(_window, pass); break; 
            case visible:
            {
                if(value) SDL_ShowWindow(_window);
                else      SDL_HideWindow(_window);
                break;
            }
            default: messageBox(ERROR, "Unable to modify window's parameter", "No such setting"); break;
        }
    }
    void Window::setSetting(windowSetting setting, float value)
    {
        switch(setting)
        {
            case brightness: SDL_SetWindowBrightness(_window, value); break;
            case opacity: SDL_SetWindowOpacity(_window, value); break;

            default: messageBox(ERROR, "Unable to modify window's parameter", "No such setting"); break;
        }
    }
    void Window::setSetting(windowSetting setting, uint16_t x, uint16_t y)
    {
        switch(setting)
        {
            case position:    _position.SET(x, y); SDL_SetWindowPosition(_window, x, y);  break; 
            case dimensions:  _size.SET(x, y); SDL_SetWindowSize(_window, x, y); break;
            case maximumSize: SDL_SetWindowMaximumSize(_window, x, y); break;
            case minimumSize: SDL_SetWindowMinimumSize(_window, x, y); break;

            default: messageBox(ERROR, "Unable to modify window's parameter", "No such setting"); break;
        }
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

    uint16_t Window::getNumberOfWindows()
    {
        return _winInfoSystem.size();
    }
    bool Window::isWindowOpenGL(uint16_t windowNumber)
    {
        if(windowNumber <= _winInfoSystem.size())
            return _winInfoSystem[windowNumber];
        return false;
    }


    void Window::initWindowRenderer()
    {
        if(_flags & SDL_WINDOW_OPENGL)
        {
            Context::init(_window);
            _winInfoSystem[_winInfoSystem.size() + 1] = true;
        }
        if(_flags & SDL_WINDOW_VULKAN)
        {
            Instance::init(_window);
            _winInfoSystem[_winInfoSystem.size() + 1] = false;
        }
    }
    void Window::update()
    {
        if(_flags & AE_WINDOW_OPENGL)
            Context::SwapBuffers();
    }


    void Window::destroy()
    {
        Context::destroy();
        Instance::destroy();
        SDL_DestroyWindow(_window);
    }

    Window::~Window()
    {
        SDL_FreeSurface(_icon);
    }
}
