// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 30/05/2022

#ifndef __AK_RENDERER_COMPONENT__
#define __AK_RENDERER_COMPONENT__

#include <Core/core.h>
#include <Graphics/entity.h>
#include <Platform/window.h>
#include <Utils/fStrings.h>
#include "Pipeline/vk_shader.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
    enum class render_mode { mode_2D, mode_3D };

    class RendererComponent : public Component
    {
        public:
            RendererComponent(WindowComponent* window);

            inline void renderingMode(render_mode mode) noexcept { _mode = mode; }

            void loadCustomShader(const fString& path, Shader::type type);

            void switchToShader(size_t index);

            void onAttach() override;
            void onRender() override;
            void onQuit() override;

        private:
            render_mode _mode;
            WindowComponent* _window = nullptr;
    };
}

#endif // __AK_RENDERER_COMPONENT__
