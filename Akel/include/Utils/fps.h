// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2021
// Updated : 31/05/2023

#ifndef __AK_FPS__
#define __AK_FPS__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak
{
	class AK_API CounterFPS
	{
		friend class Application;

		public:
			CounterFPS() = default;
			inline bool make_update() const noexcept { return make_up; }
			inline bool make_rendering() const noexcept { return make_render; }
			inline static void setTicksGoal(uint32_t ticks) noexcept { ticks_goal = ticks; ns = 1000000000.0 / ticks_goal; }
			inline static int getFPS() { return outputFPS; }
			inline static int getTicks() { return outputTicks; }
			inline static void printFPS() noexcept { std::cout << "fps : "  << outputFPS << std::endl; }	
			inline static void printTicks() noexcept { std::cout << "ticks : " << outputTicks << std::endl; }
			~CounterFPS() = default;	

		private:
			void init();
			void update();
			void renderingUpdate() noexcept;

		private:
			inline static double ns = 1000000000.0 / 60.0;
			long fps = 0;
			inline static std::atomic<long> outputFPS = 0;
			int ticks = 0;
			inline static std::atomic<int> outputTicks = 0;
			uint64_t timer = 0;
			uint64_t ticks_before = 0;
			uint64_t ticks_now = 0;
			uint32_t ticks_elapsed_time = 0;
			uint64_t rendering_before = 0;
			uint64_t rendering_now = 0;
			uint32_t rendering_elapsed_time = 0;
			inline static uint32_t ticks_goal = 60;
			bool make_up = false;
			bool make_render = false;
			std::atomic<bool> _second_passed = true;
	};		
}

#endif // __AK_FPS__

