// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 02/04/2022

#ifndef __AK_RENDERER_COMPONENT__
#define __AK_RENDERER_COMPONENT__

#include <Core/core.h>
#include <Graphics/entity.h>
#include <Platform/window.h>

#include "renderModuleHandler.h"

namespace Ak
{
    class RendererComponent : public Component
    {
        public:
            RendererComponent();
            RendererComponent(const WindowComponent* window);

            inline void add_window(const WindowComponent* window) { _module_handler.add_module(std::move(window->getRenderModule())); }

            void onAttach() override;
            void onRender() override;
            void onQuit() override;

        private:
            RenderModuleHandler _module_handler;
    };
}

#endif // __AK_RENDERER_COMPONENT__
