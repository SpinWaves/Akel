// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/03/2024
// Updated : 23/03/2024

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
