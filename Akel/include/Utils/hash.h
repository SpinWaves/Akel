// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/06/2023
// Updated : 14/06/2023

#ifndef __AK_HASH_UTILS__
#define __AK_HASH_UTILS__

#include <Akpch.h>

namespace Ak
{
	inline void hashCombine(std::size_t& seed) {}

	template <typename T, typename... Rest>
	inline void hashCombine(std::size_t& seed, const T& v, Rest... rest)
	{
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		hashCombine(seed, rest...);
	}
}

#endif
