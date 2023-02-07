// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/03/2022
// Updated : 27/01/2023

#ifndef __AK_NON_COPYABLE__
#define __AK_NON_COPYABLE__

#include <Core/profile.h>

namespace Ak
{
	class AK_API non_copyable
	{
		protected:
			non_copyable() = default;
			virtual ~non_copyable() = default;

		public:
			non_copyable(const non_copyable&) = delete;
			non_copyable(non_copyable&&) noexcept = default;
			non_copyable &operator=(const non_copyable&) = delete;
			non_copyable &operator=(non_copyable&&) noexcept = default;
	};
}

#endif // __AK_NON_COPYABLE__
