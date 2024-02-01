// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/02/2024
// Updated : 01/02/2024

#ifndef __AK_UTILS_OVERLOAD__
#define __AK_UTILS_OVERLOAD__

namespace Ak
{
	template<class... Ts>
	struct Overloaded : Ts...
	{
		using Ts::operator()...;
	};

	template<class... Ts>
	Overloaded(Ts...) -> Overloaded<Ts...>;
}

#endif
