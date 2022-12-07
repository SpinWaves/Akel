// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 07/12/2022

#ifndef __AK_RENDERER_COMPONENT__
#define __AK_RENDERER_COMPONENT__

#include <Core/core.h>
#include <Graphics/entity.h>
#include <Platform/window.h>
#include <Utils/fStrings.h>
#include "Pipeline/vk_shader.h"
#include "Pipeline/vk_graphic_pipeline.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
    class RendererComponent : public Component
    {
        public:
            RendererComponent(WindowComponent* window);

            void onAttach() override;
            void onQuit() override;

        private:
			WindowComponent* _window = nullptr;
    };
}

#endif // __AK_RENDERER_COMPONENT__
