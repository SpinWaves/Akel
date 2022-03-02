// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2021
// Updated : 02/03/2022

#include <Utils/fps.h>

namespace Ak
{
	void CounterFPS::init()
	{
		timer = SDL_GetTicks();
		before = static_cast<long long>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		now = static_cast<long long>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());		
	}

	void CounterFPS::update()
	{
		now = static_cast<long long>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

        if(SDL_GetTicks() - timer > 1000)
        {
            outputFPS = fps;
			outputTicks = ticks;
			ticks = 0;
            fps = 0;
            timer += 1000;
        }

		fps++;

		elapsed_time = now - before;
		make_up = false;
		if(elapsed_time >= ns)
        {
            ticks++;
            before += ns;
			make_up = true;
		}
	}
}
