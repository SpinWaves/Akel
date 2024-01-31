// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 31/01/2024

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
