// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2021
// Updated : 31/05/2023

#include <Utils/fps.h>
#include <Platform/window.h>

namespace Ak
{
	void CounterFPS::init()
	{
		timer = SDL_GetTicks64();

		ticks_before = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		ticks_now = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());		

		rendering_before = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		rendering_now = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());		
	}

	void CounterFPS::update()
	{
		ticks_now = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

		if(SDL_GetTicks64() - timer > 1000)
		{
			outputTicks = ticks;
			ticks = 0;
			timer += 1000;
			_second_passed = true;
		}

		ticks_elapsed_time = ticks_now - ticks_before;
		if(ticks_elapsed_time >= ns)
		{
			ticks++;
			ticks_before += ns;
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
		if(!WindowComponent::areThereWindowFocus())
		{
			rendering_now = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
			rendering_elapsed_time = rendering_now - rendering_before;
			if(rendering_elapsed_time >= 1000000000.0 / 15.0)
			{
				rendering_before += 1000000000.0 / 15.0;
				make_render = true;
				fps++;
			}
			else
				make_render = false;
		}
		else
		{
			make_render = true;
			fps++;
		}
	}
}
