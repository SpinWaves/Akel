// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2021
// Updated : 30/03/2022

#include <Platform/platform.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
    Input::Input()
    {
        for(int i = 0; i < SDL_NUM_SCANCODES; i++)
        {
            _keys[i].first = false;
            _keys[i].second = false;
            if(i < _mouse.size())
            {
                _mouse[i].first = false;
                _mouse[i].second = false;
            }
        }
    }

    void Input::update()
    { 
        if(_event.window.event == SDL_WINDOWEVENT_CLOSE) 
            _end = true;

        if(_event.type == SDL_MOUSEMOTION) 
        {
            _x = _event.motion.x;
            _y = _event.motion.y;

            _xRel = _event.motion.xrel;
            _yRel = _event.motion.yrel;

            _current_window = _event.motion.windowID;
        }

        if(_event.window.event == SDL_WINDOWEVENT_RESIZED || _event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            Render_Core::get().requireFrameBufferResize();
            for(auto win : _windows)
            {
                if(win->_window_id == _current_window)
                    win->size.SET(_event.window.data1, _event.window.data2);
            }
        }

        if(_event.window.event == SDL_WINDOWEVENT_MOVED)
        {
            for(auto win : _windows)
            {
                if(win->_window_id == _current_window)
                    win->pos.SET(_event.window.data1, _event.window.data2);
            }
        }

        switch(_event.type) 
        {
            case SDL_KEYDOWN: 
                _keys[_event.key.keysym.scancode].first = true;
                _keys[_event.key.keysym.scancode].second = false;
            break;

            case SDL_KEYUP: 
                _keys[_event.key.keysym.scancode].first = false;
                _keys[_event.key.keysym.scancode].second = true;
            break;

            case SDL_MOUSEBUTTONDOWN: 
                _mouse[_event.button.button].first = true;
                _mouse[_event.button.button].second = false;
            break;

            case SDL_MOUSEBUTTONUP: 
                _mouse[_event.button.button].first = false;
                _mouse[_event.button.button].second = true;
            break;

            default: break;
        }
    }
}
