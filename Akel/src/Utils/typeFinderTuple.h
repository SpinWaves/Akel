// This file is a part of Akel
// CREATED : 14/06/2021
// UPDATED : 17/06/2021

#ifndef __AK_TYPE_FINDER_TUPLE__
#define __AK_TYPE_FINDER_TUPLE__

namespace Ak
{
	//template<typename T, typename First, typename... Rest>
	//struct tuple_element_index_helper;	// Declaration

	//template<typename T>
	//struct tuple_element_index_helper<T, std::tuple<>> // Specialization
	//{
		//static constexpr std::size_t value = 0;
	//};

	//template<typename T, typename... Rest>
	//struct tuple_element_index_helper<T, std::tuple<T, Rest...>> // Specialization
	//{
		//static constexpr std::size_t value = 0;
		//using RestTuple = std::tuple<Rest...>;
		//static_assert(tuple_element_index_helper<T, RestTuple>::value == std::tuple_size_v<RestTuple>, "type appears more than once in tuple");
	//};

	//template <typename T, typename First, typename... Rest>
	//struct tuple_element_index_helper<T, std::tuple<First, Rest...>> // Specialization
	//{
		//using RestTuple = std::tuple<Rest...>;
		//static constexpr std::size_t value = 1 + tuple_element_index_helper<T, RestTuple>::value;
	//};

	//template <typename T, typename Tuple>
	//struct tuple_element_finder	// Finder 
	//{
		//static constexpr std::size_t value = tuple_element_index_helper<T, Tuple>::value;
		//static_assert(value < std::tuple_size_v<Tuple>, "there is no component with that type");
	//};

	//template<typename T, typename Tuple>
	//inline constexpr std::size_t tuple_element_finder_v = tuple_element_finder<T, Tuple>::value;

	template< size_t I, typename T, typename Tuple_t>
	constexpr size_t index_in_tuple_fn()
	{
		static_assert(I < std::tuple_size<Tuple_t>::value, "The element is not in the tuple");
		typedef typename std::tuple_element<I, Tuple_t>::type el;
		if constexpr(std::is_same<T, el>::value)
			return I;
		return index_in_tuple_fn<I + 1, T, Tuple_t>();
	}

	template<typename T, typename Tuple_t>
	struct index_in_tuple
	{
		static constexpr size_t value = index_in_tuple_fn<0, T, Tuple_t>();
	};

	template<typename T, typename Tuple>
	inline constexpr std::size_t index_in_tuple_v = index_in_tuple<T, Tuple>::value;
}

// DOCUMENTATION
// This tool is used like that:
//
// size_t rank = Ak::tuple_element_finder<*TypeToFind*, *YourTuple*>::value;
//							OR
// size_t rank = Ak::tuple_element_finder_v<*TypeToFind*, *YourTuple*>;
//

#endif // __AK_TYPE_FINDER_TUPLE__

