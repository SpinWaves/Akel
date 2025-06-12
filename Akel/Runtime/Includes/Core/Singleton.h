// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_SINGLETON_H
#define AK_CORE_SINGLETON_H

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
