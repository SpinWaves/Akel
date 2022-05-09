// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/03/2022
// Updated : 09/05/2022

#include <Utils/plainApplication.h>

namespace Ak
{
    PlainApplication::PlainApplication(const char* name) : Application(name)
    {
        window = memAlloc<WindowComponent>();
        if(name != nullptr)
            window->title = name;
        add_component(window);
        
        renderer = memAlloc<RendererComponent>(window);
        renderer->renderingMode(render_mode::mode_3D);
        add_component(renderer);
    }
}
