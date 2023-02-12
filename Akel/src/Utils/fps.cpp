// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2021
// Updated : 11/02/2023

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
            outputFPS = fps;
			outputTicks = ticks;
			ticks = 0;
            fps = 0;
            timer += 1000;
        }

		fps++;

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
}
