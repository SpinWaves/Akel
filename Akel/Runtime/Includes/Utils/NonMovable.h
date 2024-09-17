// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_UTILS_NON_MOVABLE__
#define __AK_UTILS_NON_MOVABLE__

namespace Ak
{
	class NonMovable
	{
		protected:
			NonMovable() = default;
			virtual ~NonMovable() = default;

		public:
			NonMovable(const NonMovable&) = default;
			NonMovable(NonMovable&&) noexcept = delete;
			NonMovable& operator=(const NonMovable&) = default;
			NonMovable& operator=(NonMovable&&) noexcept = delete;
	};
}

#endif
