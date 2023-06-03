// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/06/2023
// Updated : 03/06/2023

#include <Renderer/fps.h>

namespace Ak
{
	void CounterFPS::init()
	{
		_timer = SDL_GetTicks64();

		_fps_before = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		_fps_now = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());		
	}

	void CounterFPS::update()
	{
		_fps_now = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

		if(SDL_GetTicks64() - _timer > 1000)
		{
			_output_fps = _fps;
			_fps = 0;
			_timer += 1000;
		}

		_fps_elapsed_time = _fps_now - _fps_before;
		if(_fps_elapsed_time >= _ns)
		{
			_fps++;
			_fps_before += _ns;
			_make_render = true;
		}
		else
			_make_render = false;
	}
}
