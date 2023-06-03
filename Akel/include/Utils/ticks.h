// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2021
// Updated : 03/06/2023

#ifndef __AK_TICKS__
#define __AK_TICKS__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak
{
	class AK_API CounterTicks
	{
		friend class Application;

		public:
			CounterTicks() = default;
			inline bool makeUpdate() const noexcept { return _make_up; }
			inline static void setTicksGoal(uint32_t ticks) noexcept { _ticks_goal = ticks; _ns = 1000000000.0 / _ticks_goal; }
			inline static int getTicks() { return _output_ticks; }
			inline static void printTicks() noexcept { std::cout << "ticks : " << _output_ticks << std::endl; }
			~CounterTicks() = default;	

		private:
			void init();
			void update();

		private:
			inline static double _ns = 1000000000.0 / 60.0;
			uint64_t _timer = 0;
			uint64_t _ticks_before = 0;
			uint64_t _ticks_now = 0;
			inline static uint32_t _ticks_goal = 60;
			uint32_t _ticks_elapsed_time = 0;
			uint32_t _ticks = 0;
			inline static int _output_ticks = 0;
			bool _make_up = false;
	};		
}

#endif // __AK_TICKS__

