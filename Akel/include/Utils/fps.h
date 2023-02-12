// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2021
// Updated : 11/02/2023

#ifndef __AK_FPS__
#define __AK_FPS__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak
{
	class AK_API CounterFPS
    {
        public:
            CounterFPS() = default;
			void init();
			void update();
			inline bool make_update() const noexcept { return make_up; }
			inline static int getFPS() { return outputFPS; }
			inline static int getTicks() { return outputTicks; }
			inline static void printFPS() noexcept { std::cout << "fps : "  << outputFPS << std::endl; }	
			inline static void printTicks() noexcept { std::cout << "ticks : " << outputTicks << std::endl; }
			~CounterFPS() = default;	
        
		private:
			long fps = 0;
			inline static long outputFPS = 0;
			int ticks = 0;
			inline static int outputTicks = 0;
			double ns = 1000000000.0 / 60.0;
			uint64_t timer = 0;
			uint64_t before = 0;
			uint64_t now = 0;
			uint32_t elapsed_time = 0;
			bool make_up = false;
    };		
}

#endif // __AK_FPS__

