// This file is a part of Akel
// CREATED : 29/04/2021
// UPDATED : 03/06/2021

#ifndef __AK_FPS__
#define __AK_FPS__

#include <Akpch.h>

namespace Ak
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
			long fps = 0;
			long outputFPS = 0;
			int ticks = 0;
			int outputTicks = 0;
			double ns = 1000000000.0 / 60.0;
			uint32_t elapsed_time = 0;
			uint32_t timer = 0;
			long long before = 0;			
			long long now = 0;
			bool second_passed = false;	
    };		
}

#endif // __AK_FPS__

