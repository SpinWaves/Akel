// This file is a part of Akel
// CREATED : 05/04/2021
// UPDATED : 05/04/2021

#include <Utils/utils.h>

namespace Ak
{
    std::ostream &operator<<(std::ostream &os, const Code code)
    {
        return os << "\033[1;" << std::to_string(code) << "m";       // Print std::cout with colors or effects
    }
}
