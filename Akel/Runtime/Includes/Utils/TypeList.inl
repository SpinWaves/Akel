// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/02/2024
// Updated : 06/02/2024

#pragma once
#include <Utils/TypeList.h>

namespace Ak
{
	namespace Internal
	{
		template<typename Type, std::uint64_t index_>
		struct TypeListItem
		{
			using type = Type;
			static constexpr const std::uint64_t index = index_;
		};

		// get
		template<std::uint64_t index, typename T, typename... TS>
		struct GetNthTypeInner;

		template<typename T, typename... TS>
		struct GetNthTypeInner<0, T, TS...>
		{
			using type = T;
		};

		template<std::uint64_t index, typename T, typename... TS>
		struct GetNthTypeInner
		{
			using type = typename GetNthTypeInner<index - 1, TS...>::type;
		};

		template<std::uint64_t index, typename... TS>
		struct GetNthType
		{
			using type = typename GetNthTypeInner<index, TS...>::type;
		};

		template<std::uint64_t index>
		struct GetNthType<index>
		{};

		// enumerate
		template<std::uint64_t index, typename T, typename... TS>
		struct EnumerateImplInner;

		template<std::uint64_t index, typename... TS>
		struct EnumerateImpl
		{
			using type = typename EnumerateImplInner<index, TS...>::type;
		};

		template<std::uint64_t index>
		struct EnumerateImpl<index>
		{
			using type = TypeList<>;
		};

		template<std::uint64_t index, typename T, typename... TS>
		struct EnumerateImplInner
		{
			using type = typename EnumerateImpl<index + 1, TS...>::type::template PushFront<TypeListItem<T, index>>;
		};

		// keep
		template<typename L, std::uint64_t i, std::uint64_t... indices>
		struct KeepImplInner;

		template<typename L, std::uint64_t... indices>
		struct KeepImpl
		{
			using type = typename KeepImplInner<L, indices...>::type;
		};

		template<typename L>
		struct KeepImpl<L>
		{
			using type = TypeList<>;
		};

		template<typename L, std::uint64_t i, std::uint64_t... indices>
		struct KeepImplInner
		{
			using _tail_type = typename KeepImpl<L, indices...>::type;
			using _ith_type = typename L::template Get<i>;
			using type = typename _tail_type::template PushFront<_ith_type>;
		};

		// Find
		struct FinderHelper
		{
			template<std::size_t Index, typename ToFind, typename Type, typename... Rest> static constexpr std::size_t Find()
			{
				if constexpr(std::is_same_v<ToFind, Type>)
					return Index;
				else
					return Find<Index + 1, ToFind, Rest...>();
			}

			template<std::size_t Index, typename ToFind> static constexpr std::size_t Find()
			{
				return std::numeric_limits<std::size_t>::max();
			}
		};

		template<typename TypeToFind, typename... ListTypes>
		struct Finder
		{
			static constexpr std::size_t Find()
			{
				return FinderHelper::Find<0, TypeToFind, ListTypes...>();
			}
		};
	}

	template<typename... T>
	template<typename Func>
	void TypeList<T...>::ForEachHelper(const Func& func)
	{
		auto wrapper = [&](auto t)
		{
			func(t);
			return 1;
		};
		std::make_tuple(wrapper(T())...);
	}

	template<typename... T>
	template<typename Func>
	void TypeList<T...>::ForEach(const Func& func)
	{
		Enumerate::template ForEachHelper<Func>(func);
	}

	template<typename... T>
	template<template<typename...> class U, typename Func>
	auto TypeList<T...>::ForEachAndCollectHelper(const Func& func) -> U<decltype(func(T()))...>
	{
		return U<decltype(func(T()))...>(func(T())...);
	}

	template<typename... T>
	template<template<typename...> class U, typename Func>
	auto TypeList<T...>::ForEachAndCollect(const Func& func)
	{
		return Enumerate::template ForEachAndCollectHelper<U, Func>(func);
	}
}
