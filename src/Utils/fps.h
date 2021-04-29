// This file is a part of AtlasEngine
// CREATED : 29/04/2021
// UPDATED : 29/04/2021

#ifndef __FPS__
#define __FPS__

#include <AEpch.h>

namespace AE
{
	class CounterFPS
    {
        public:
            CounterFPS();
			void start();
			void update();
			int getFPS();
			int getTicks();
			void printFPS();
			void printTicks();
			~CounterFPS();	
        
		private:
			int fps = 0;
			int outputFPS = 0;
			int ticks;
			int outputTicks;
			double ns = 1000000000.0 / 60.0;
			uint32_t elapsed_time;
			uint32_t timer;
			long long before;			
			long long now;
			bool second_passed = false;	
    };		
}

#endif // __FPS__

