#include "rectComponent.h"

RectComponent::RectComponent() : Ak::WindowComponent(), Ak::RendererComponent(this) {}

void RectComponent::onAttach()
{
    Ak::WindowComponent::create();
    Ak::WindowComponent::setSetting<title>("Rectangle using Akel Engine");
    Ak::WindowComponent::setSetting<dimensions>(1280, 750);
    Ak::WindowComponent::setSetting<resizable>(false);

    Ak::RendererComponent::onAttach();
}

void RectComponent::onEvent(Ak::Input& input)
{
    Ak::WindowComponent::onEvent(input);
    Ak::RendererComponent::onEvent(input);
}

void RectComponent::update()
{
    Ak::WindowComponent::update();
    Ak::RendererComponent::update();
}

void RectComponent::onQuit()
{
    Ak::RendererComponent::onQuit();
    Ak::WindowComponent::onQuit();
}
