// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/03/2022
// Updated : 28/03/2022

#ifndef __AK_SELF_INSTANCE__
#define __AK_SELF_INSTANCE__

#include "core.h"
#include <Utils/plateformUtils.h>

namespace Ak
{
	template <typename T>
	class SelfInstance : public non_copyable
	{
		public:			
			inline static T& get()
			{
				static T instance;
				return instance;
			}
	};
}

#endif // __AK_SELF_INSTANCE__
