// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once
#include <Core/VirtualDirectory.h>

namespace Ak
{
	template <typename F>
	void VirtualDirectory::ForEachEntries(F&& f)
	{
		static_assert(std::is_invocable_v<F(const Entry)>, "Ak::VirtualDirectory::ForEachEntries given callback is invalid");
		for(auto&& entry : m_entries)
			f(std::as_const(entry));
	}
}
