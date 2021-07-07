// This file is a part of Akel
// CREATED : 29/04/2021
// UPDATED : 06/07/2021

#ifndef __AK_FPS__
#define __AK_FPS__

#include <Akpch.h>
#include <Core/Components/components.h>

namespace Ak
{
	class CounterFPS : public Component
    {
        public:
            CounterFPS();
			void onAttach() override;
			void update() override;
			static int getFPS();
			static int getTicks();
			static void printFPS();
			static void printTicks();
			~CounterFPS() = default;	
        
		private:
			long fps = 0;
			inline static long outputFPS = 0;
			int ticks = 0;
			inline static int outputTicks = 0;
			double ns = 1000000000.0 / 60.0;
			uint32_t elapsed_time = 0;
			uint32_t timer = 0;
			long long before = 0;			
			long long now = 0;
			inline static bool second_passed = false;	
    };		
}

#endif // __AK_FPS__

