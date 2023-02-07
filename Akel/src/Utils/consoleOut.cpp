// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/04/2021
// Updated : 05/04/2021

#include <Utils/utils.h>

namespace Ak
{
    std::ostream &operator<<(std::ostream &os, const Code code)
    {
        return os << "\033[1;" << std::to_string(code) << "m";       // Print std::cout with colors or effects
    }
}
