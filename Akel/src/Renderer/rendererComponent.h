// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 05/04/2022

#ifndef __AK_RENDERER_COMPONENT__
#define __AK_RENDERER_COMPONENT__

#include <Core/core.h>
#include <Graphics/entity.h>
#include <Platform/window.h>

namespace Ak
{
    enum class render_mode { 2D, 3D };

    class RendererComponent : public Component
    {
        public:
            RendererComponent();
            RendererComponent(WindowComponent* window);

            void setRenderMode(render_mode mode);

            void onAttach() override;
            void onRender() override;
            void onQuit() override;
    };
}

#endif // __AK_RENDERER_COMPONENT__
