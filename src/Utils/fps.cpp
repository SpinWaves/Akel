// This file is a part of Akel
// CREATED : 29/04/2021
// UPDATED : 29/04/2021

#include <Utils/utils.h>

namespace Ak
{
	CounterFPS::CounterFPS()
	{}

	void CounterFPS::start()
	{
		timer = SDL_GetTicks();
		before = static_cast<long long>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		now = static_cast<long long>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());		
	}

	void CounterFPS::printFPS()
	{
		if(second_passed)
			std::cout << "fps : "  << outputFPS << std::endl;
	}
	
	void CounterFPS::printTicks()
	{
		if(second_passed)
			std::cout << "ticks : " << outputTicks << std::endl;
	}

	void CounterFPS::update()
	{
		now = static_cast<long long>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

        if(SDL_GetTicks() - timer > 1000)
        {
			second_passed = true;
            outputFPS = fps;
			outputTicks = ticks;
			ticks = 0;
            fps = 0;
            timer += 1000;
        }
		else
			second_passed = false;

		fps++;

		elapsed_time = now - before;
		if(elapsed_time >= ns)
        {
            ticks++;
            before += ns;
		}
	}

	int CounterFPS::getFPS()
	{
		return outputFPS;
	}

	int CounterFPS::getTicks()
	{
		return outputTicks;
	}

	CounterFPS::~CounterFPS()
	{}
}

