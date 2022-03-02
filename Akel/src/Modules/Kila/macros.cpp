// This file is a part of Akel
// Author : @kbz_8
// CREATED : 15/11/2021
// UPDATED : 15/11/2021

#include <Modules/Kila/macros.h>

namespace Ak::Kl
{
    bool Macros::have_once(const std::string& name)
    {
        for(auto& elem : _onces)
        {
            if(elem == name)
                return true;
        }
        return false;
    }
}
