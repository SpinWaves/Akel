// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/06/2023
// Updated : 30/06/2023

#ifndef __AK_BASE_EVENT__
#define __AK_BASE_EVENT__

namespace Ak
{
	class BaseEvent
	{
		public:
			BaseEvent() = default;
			const char* what() const = 0;
			virtual BaseEvent() = default;
	};
}

#endif
