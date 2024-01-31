// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 31/01/2024

#ifndef __AK_CORE_SINGLETON__
#define __AK_CORE_SINGLETON__

#include <Utils/NonCopyable.h>

namespace Ak
{
	template <typename T>
	class Singleton : public NonCopyable
	{
		public:
			inline static T& Get()
			{
				static T instance;
				return instance;
			}
	};
}

#endif
