// This file is a part of Akel
// Authors : @kbz_8
// Created : 13/07/2021
// Updated : 27/03/2023

#ifndef __AK_TIME__
#define __AK_TIME__

#include <Akpch.h>
#include <Core/profile.h>

struct __time
{
	uint8_t sec = 0;   // 0-59
	uint8_t min = 0;   // 0-59
	uint8_t hour = 0;  // 0-23
	uint8_t day = 1;   // 1-30/31
	uint8_t month = 1; // 1-12
	uint32_t year = 0;
};

namespace Ak
{
	class AK_API Time
	{
		public:
			static __time& getCurrentTime();
			static void delay(long pause);	// This avoid you to link SDL2 to use SDL_Delay

		private:
			inline static std::tm* _now;
			inline static __time _time;
	};
}

#endif // __AK_TIME__
