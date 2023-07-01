// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2021
// Updated : 02/07/2023

#include <Core/Event/event.h>
#include <Platform/platform.h>
#include <Renderer/renderer_events.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
	Input::Input()
	{
		reset();
	}

	void Input::reset() noexcept
	{
		_xRel = 0;
		_yRel = 0;
		for(int i = 0; i < _keys.size(); i++)
			_keys[i] = _keys[i] & ~(static_cast<uint8_t>(action::up));
		for(int i = 0; i < _mouse.size(); i++)
			_mouse[i] = _mouse[i] & ~(static_cast<uint8_t>(action::up));
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
					if((*it)->_renderer != -1)
						EventBus::send("_renderer_component" + std::to_string((*it)->_renderer), RenderQuitEvent{});
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

			SDL_GetGlobalMouseState(&_gx, &_gy);
		}

		if(_event.window.event == SDL_WINDOWEVENT_RESIZED || _event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			for(auto win : _windows)
			{
				if(win->_window_id == _current_window)
				{
					win->size.set(_event.window.data1, _event.window.data2);
					if(win->_renderer != -1)
						EventBus::send("_renderer_component" + std::to_string(win->_renderer), ResizeEvent{});
				}
			}
		}

		if(_event.window.event == SDL_WINDOWEVENT_MINIMIZED)
		{
			for(auto win : _windows)
			{
				if(win->_window_id == _current_window)
				{
					win->minimize = true;
					if(win->_renderer != -1)
						EventBus::send("_renderer_component" + std::to_string(win->_renderer), ResizeEvent{});
				}
			}
		}
		else if(_event.window.event == SDL_WINDOWEVENT_MAXIMIZED)
		{
			for(auto win : _windows)
			{
				if(win->_window_id == _current_window)
				{
					win->maximize = true;
					if(win->_renderer != -1)
						EventBus::send("_renderer_component" + std::to_string(win->_renderer), ResizeEvent{});
				}
			}
		}
		else if(_event.window.event == SDL_WINDOWEVENT_RESTORED)
		{
			for(auto win : _windows)
			{
				if(win->_window_id == _current_window)
				{
					win->minimize = false;
					win->maximize = false;
					if(win->_renderer != -1)
						EventBus::send("_renderer_component" + std::to_string(win->_renderer), ResizeEvent{});
				}
			}
		}
		else if(_event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
		{
			for(auto win : _windows)
			{
				if(win->_window_id == _current_window)
					win->_window_has_focus = false;
			}
		}
		else if(_event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
		{
			for(auto win : _windows)
			{
				if(win->_window_id == _current_window)
					win->_window_has_focus = true;
			}
		}
		else if(_event.window.event == SDL_WINDOWEVENT_MOVED)
		{
			for(auto win : _windows)
			{
				if(win->_window_id == _current_window)
					win->pos.set(_event.window.data1, _event.window.data2);
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
