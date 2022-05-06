// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 06/05/2022

#ifndef __AK_RENDERER_COMPONENT__
#define __AK_RENDERER_COMPONENT__

#include <Core/core.h>
#include <Graphics/entity.h>
#include <Platform/window.h>
#include <Utils/fStrings.h>
#include "pipeline/vk_shader.h"

namespace Ak
{
    enum class render_mode { 2D, 3D };

    class RendererComponent : public Component
    {
        public:
            RendererComponent();
            RendererComponent(WindowComponent* window);

            void renderingMode(render_mode mode);

            void loadCustomShader(const fString& path, Shader::type type);
            void loadCustomShader(const fString& path);

            void switchToShader(size_t index);

            void onAttach() override;
            void onRender() override;
            void onQuit() override;
    };
}

#endif // __AK_RENDERER_COMPONENT__
