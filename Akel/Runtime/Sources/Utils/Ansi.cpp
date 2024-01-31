// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 31/01/2024

#include <Utils/Ansi.h>

namespace Ak
{
	std::ostream &operator<<(std::ostream& os, Ansi ansi)
	{
		return os << "\033[1;" << std::to_string(static_cast<std::uint32_t>(ansi)) << "m";
	}
}
