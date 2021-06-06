// This file is a part of Akel
// CREATED : 05/04/2021
// UPDATED : 03/06/2021

#ifndef __AK_CONSOLE_OUT__
#define __AK_CONSOLE_OUT__

#include <Akpch.h>

namespace Ak
{
    enum Code
    {
        red = 31,
        green = 32,
        blue = 34,
        def = 39,
        black = 30,
        yellow = 33,
        magenta = 35,
        cyan = 36,
        white = 37,
        bg_red = 41,
        bg_green = 42,
        bg_blue = 44,
        bg_def = 49,
        bg_black = 40,
        bg_yellow = 43,
        bg_magenta = 45,
        bg_cyan = 46,
        bg_white = 47,
        reset = 0,
        bold = 1,
        underline = 4,
        inverse = 7,
        bold_off = 21,
        underline_off = 24,
        inverse_off = 27
    };

    std::ostream &operator<<(std::ostream &os, const Code code); // Print std::cout with colors or effects
}

#endif // __AK_CONSOLE_OUT__
