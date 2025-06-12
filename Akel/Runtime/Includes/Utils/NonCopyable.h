// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_UTILS_NON_COPYABLE_H
#define AK_UTILS_NON_COPYABLE_H

namespace Ak
{
	class NonCopyable
	{
		protected:
			NonCopyable() = default;
			virtual ~NonCopyable() = default;

		public:
			NonCopyable(const NonCopyable&) = delete;
			NonCopyable(NonCopyable&&) noexcept = default;
			NonCopyable& operator=(const NonCopyable&) = delete;
			NonCopyable& operator=(NonCopyable&&) noexcept = default;
	};
}

#endif
