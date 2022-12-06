// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/03/2022
// Updated : 06/12/2022

#include <Utils/plainApplication.h>

namespace Ak
{
    PlainApplication::PlainApplication(const char* name) : Application()
    {
        window = memAlloc<WindowComponent>();
        if(name != nullptr)
            window->title = name;
        add_component(window);
        
        renderer = memAlloc<RendererComponent>(window);
        add_component(renderer);
    }
}
