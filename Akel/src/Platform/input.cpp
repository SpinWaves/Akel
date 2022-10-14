// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2021
// Updated : 14/10/2022

#include <Platform/platform.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
    Input::Input()
    {
		reset();
    }

    void Input::update()
    { 
		_current_window = _event.window.windowID;
        if(_event.window.event == SDL_WINDOWEVENT_CLOSE) 
		{
			if(_windows.size() == 1)
			{
            	_end = true;
				return;
			}
			for(auto it = _windows.begin(); it != _windows.end(); it++)
			{
				if((*it)->_window_id == _current_window)
				{
					(*it)->onQuit();
					_windows.erase(it);
					break;
				}
			}
		}

        if(_event.type == SDL_MOUSEMOTION) 
        {
            _x = _event.motion.x;
            _y = _event.motion.y;

            _xRel = _event.motion.xrel;
            _yRel = _event.motion.yrel;
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

        if(_event.window.event == SDL_WINDOWEVENT_MINIMIZED)
        {
            Render_Core::get().requireFrameBufferResize();
            for(auto win : _windows)
            {
                if(win->_window_id == _current_window)
                    win->minimize = true;
            }
        }
        else if(_event.window.event == SDL_WINDOWEVENT_MAXIMIZED)
        {
            Render_Core::get().requireFrameBufferResize();
            for(auto win : _windows)
            {
                if(win->_window_id == _current_window)
                    win->maximize = true;
            }
        }
        else if(_event.window.event == SDL_WINDOWEVENT_RESTORED)
        {
            Render_Core::get().requireFrameBufferResize();
            for(auto win : _windows)
            {
                if(win->_window_id == _current_window)
                {
                    win->minimize = false;
                    win->maximize = false;
                }
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
            case SDL_KEYDOWN:			_keys[_event.key.keysym.scancode] = static_cast<uint8_t>(action::down); break;
            case SDL_KEYUP:				_keys[_event.key.keysym.scancode] = static_cast<uint8_t>(action::up); break;
            case SDL_MOUSEBUTTONDOWN:	_mouse[_event.button.button] = static_cast<uint8_t>(action::down); break;
            case SDL_MOUSEBUTTONUP:		_mouse[_event.button.button] = static_cast<uint8_t>(action::up); break;

            default: break;
        }
    }
}
