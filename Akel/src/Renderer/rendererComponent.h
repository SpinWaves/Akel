// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 28/03/2022

#ifndef __AK_RENDERER_COMPONENT__
#define __AK_RENDERER_COMPONENT__

#include <Core/core.h>
#include <Graphics/entity.h>
#include <Platform/window.h>

namespace Ak
{
    class RendererComponent : public Component
    {
        public:
             RendererComponent();
             RendererComponent(WindowComponent* window);

             void onAttach() override;
             void onRender() override;
             void onQuit() override;
    };
}

#endif // __AK_RENDERER_COMPONENT__
