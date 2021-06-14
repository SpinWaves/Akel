// This file is a part of Akel
// CREATED : 14/06/2021
// UPDATED : 14/06/2021

#ifndef ___AK_TYPE_FINDER_TUPLE___AK_TYPE_FINDER_TUPLE__
#define ___AK_TYPE_FINDER_TUPLE___AK_TYPE_FINDER_TUPLE__

namespace Ak
{
	template<typename T, typename First, typename... Rest>
	struct tuple_element_index_helper;	// Declaration

	template<typename T>
	struct tuple_element_index_helper<T, std::tuple<>> // Specialization
	{
		static constexpr std::size_t value = 0;
	};

	template<typename T, typename... Rest>
	struct tuple_element_index_helper<T, std::tuple<T, Rest...>> // Specialization
	{
		static constexpr std::size_t value = 0;
		using RestTuple = std::tuple<Rest...>;
		static_assert(tuple_element_index_helper<T, RestTuple>::value == std::tuple_size_v<RestTuple>, "type appears more than once in tuple");
	};

	template <typename T, typename First, typename... Rest>
	struct tuple_element_index_helper<T, std::tuple<First, Rest...>> // Specialization
	{
		using RestTuple = std::tuple<Rest...>;
		static constexpr std::size_t value = 1 + tuple_element_index_helper<T, RestTuple>::value;
	};

	template <typename T, typename Tuple>
	struct tuple_element_finder	// Finder 
	{
		static constexpr std::size_t value = tuple_element_index_helper<T, Tuple>::value;
		static_assert(value < std::tuple_size_v<Tuple>, "there is no component with that type");
	};

	template<typename T, typename Tuple>
	inline constexpr std::size_t tuple_element_finder_v = tuple_element_finder<T, Tuple>::value;
}

// DOCUMENTATION
// This tool is used like that:
//
// size_t rank = Ak::tuple_element_finder<*TypeToFind*, *YourTuple*>::value;
//							OR
// size_t rank = Ak::tuple_element_finder_v<*TypeToFind*, *YourTuple*>;
//

#endif // ___AK_TYPE_FINDER_TUPLE___AK_TYPE_FINDER_TUPLE__

