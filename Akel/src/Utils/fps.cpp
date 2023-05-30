// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2021
// Updated : 30/05/2023

#include <Utils/fps.h>

namespace Ak
{
	void CounterFPS::init()
	{
		timer = SDL_GetTicks64();
		before = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		now = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());		
	}

	void CounterFPS::update()
	{
		now = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

		if(SDL_GetTicks64() - timer > 1000)
		{
			outputTicks = ticks;
			ticks = 0;
			timer += 1000;
			_second_passed = true;
		}

		elapsed_time = now - before;
		if(elapsed_time >= ns)
		{
			ticks++;
			before += ns;
			make_up = true;
		}
		else
			make_up = false;
	}

	void CounterFPS::renderingUpdate() noexcept
	{
		if(_second_passed)
		{
			outputFPS = fps;
			fps = 0;
			_second_passed = false;
		}
		fps++;
	}
}
