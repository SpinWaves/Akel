// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2021
// Updated : 29/10/2023

#include <Utils/ticks.h>

namespace Ak
{
	void CounterTicks::init()
	{
		_timer = SDL_GetTicks64();

		_ticks_before = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		_ticks_now = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());		
	}

	void CounterTicks::update()
	{
		_ticks_now = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

		if(SDL_GetTicks64() - _timer > 1000)
		{
			_output_ticks = _ticks;
			_ticks = 0;
			_timer += 1000;
		}

		_ticks_elapsed_time = _ticks_now - _ticks_before;
		if(_ticks_elapsed_time >= _ns)
		{
			_ticks++;
			_ticks_before += _ns;
			_make_up = true;
		}
		else
		{
			_make_up = false;
			std::this_thread::sleep_for(std::chrono::duration<double, std::nano>(_ns));
		}
	}
}
