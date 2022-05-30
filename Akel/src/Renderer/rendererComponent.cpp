// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 30/05/2022

#include <Renderer/rendererComponent.h>

namespace Ak
{
    RendererComponent::RendererComponent(WindowComponent* window) : Component("__renderer_component"), _window(window) {}

    void RendererComponent::onAttach()
    {
        Render_Core::get().setWindow(_window);
        Render_Core::get().init();
    }

    void RendererComponent::onRender()
    {
        
    }

    void RendererComponent::onQuit()
    {
        Render_Core::get().destroy();
    }
}
