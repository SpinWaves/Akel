// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_TYPE_LIST__
#define __AK_TYPE_LIST__

#include <Utils/PreCompiled.h>

// Base code from https://github.com/lipk/cpp-typelist

namespace Ak
{
	namespace Internal
	{
		template<typename, std::uint64_t>
		struct TypeListItem;

		template<std::uint64_t, typename, typename...>
		struct GetNthTypeInner;

		template<typename T, typename... TS>
		struct GetNthTypeInner<0, T, TS...>;

		template<std::uint64_t, typename, typename...>
		struct GetNthTypeInner;

		template<std::uint64_t, typename...>
		struct GetNthType;

		template<std::uint64_t index>
		struct GetNthType<index>;

		template<std::uint64_t, typename, typename...>
		struct EnumerateImplInner;

		template<std::uint64_t, typename...>
		struct EnumerateImpl;

		template<std::uint64_t index>
		struct EnumerateImpl<index>;

		template<std::uint64_t, typename, typename...>
		struct EnumerateImplInner;

		template<typename, std::uint64_t, std::uint64_t...>
		struct KeepImplInner;

		template<typename, std::uint64_t...>
		struct KeepImpl;

		template<typename L>
		struct KeepImpl<L>;

		template<typename, std::uint64_t, std::uint64_t...>
		struct KeepImplInner;

		template<typename, typename...>
		struct Finder;
	}

	template<typename... T>
	struct TypeList
	{
		// Compile time operations
		template<template<typename> class W>
		using Wrap = TypeList<W<T>...>;

		template<template<typename> class M>
		using Map = TypeList<typename M<T>::type...>;

		template<typename TT>
		using PushBack = TypeList<T..., TT>;

		template<typename TT>
		using PushFront = TypeList<TT, T...>;

		template<std::uint64_t index>
		using Get = typename Internal::GetNthType<index, T...>::type;

		using Enumerate = typename Internal::EnumerateImpl<0, T...>::type;

		template<std::uint64_t... indices>
		using Keep = typename Internal::KeepImpl<TypeList<T...>, indices...>::type;

		template<typename TT>
		constexpr static std::size_t Find = Internal::Finder<TT, T...>::Find();

		template<typename TT>
		constexpr static bool Has = Find<TT> != std::numeric_limits<std::size_t>::max();

		// Runtime operations
		template<typename Func>
		static void ForEachHelper(const Func& func);

		template<typename Func>
		static void ForEach(const Func& func);

		template<template<typename...> class U, typename Func>
		static auto ForEachAndCollectHelper(const Func& func) -> U<decltype(func(T()))...>;

		template<template<typename...> class U, typename Func>
		static auto ForEachAndCollect(const Func& func);

		// Conversion
		template<template<typename...> class U>
		using To = U<T...>;

		using ToTuple = To<std::tuple>;
	};
}

#include <Utils/TypeList.inl>

#endif
