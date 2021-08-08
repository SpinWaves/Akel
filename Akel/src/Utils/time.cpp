// This file is a part of Akel
// CREATED : 13/07/2021
// UPDATED : 13/07/2021

#include <Utils/utils.h>

namespace Ak
{
	__time& Time::getCurrentTime()
	{
		_now = std::localtime(new std::time_t(std::time(0)));
		_time.sec = static_cast<uint8_t>(_now->tm_sec);
		_time.min = static_cast<uint8_t>(_now->tm_min);
		_time.hour = static_cast<uint8_t>(_now->tm_hour);
		_time.day = static_cast<uint8_t>(_now->tm_mday);
		_time.month = static_cast<uint8_t>(_now->tm_mon + 1);
		_time.year = static_cast<uint32_t>(_now->tm_year + 1900);
		return _time;
	}

	void Time::delay(long pause)
	{
		SDL_Delay(pause);
	}
}
