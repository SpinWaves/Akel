// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/06/2023
// Updated : 01/07/2023

#ifndef __AK_BASE_EVENT__
#define __AK_BASE_EVENT__

namespace Ak
{
	class AK_API BaseEvent
	{
		public:
			BaseEvent() = default;
			uint32_t what() const = 0;
			virtual BaseEvent() = default;
	};
}

#endif
