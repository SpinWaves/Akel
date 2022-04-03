// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 02/04/2022

#include <Renderer/rendererComponent.h>

namespace Ak
{
    RendererComponent::RendererComponent() : Component("__renderer_component"), _module_handler() {}
    RendererComponent::RendererComponent(const WindowComponent* window) : Component("__renderer_component"), _module_handler()
    {
    }

    void RendererComponent::onAttach()
    {
        
    }

    void RendererComponent::onRender()
    {
        
    }

    void RendererComponent::onQuit()
    {
        
    }
}
