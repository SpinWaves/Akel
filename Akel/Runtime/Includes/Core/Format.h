// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/02/2024
// Updated : 02/02/2024

#ifndef __AK_CORE_FORMAT__
#define __AK_CORE_FORMAT__

#include <Core/PreCompiled.h>

namespace Ak
{
	template<typename T, typename = void>
	struct IsOstreamable : std::false_type {};

	template<typename T>
	struct IsOstreamable<T, std::void_t<decltype(std::declval<std::ostream>() << std::declval<T>())>> : std::true_type {};

	template<typename... Args, std::enable_if_t<std::conjunction_v<IsOstreamable<Args>...>, int> = 0>
	auto Format(std::string_view format, const Args&... args);
}

#include <Core/Format.inl>

#endif
