#include "rectComponent.h"

RectComponent::RectComponent() : Ak::WindowComponent() {}

void RectComponent::onAttach()
{
    Ak::WindowComponent::onAttach();
    Ak::WindowComponent::setSetting(Ak::winsets::title, "Rectangle using Akel Engine");
    Ak::WindowComponent::setSetting(Ak::winsets::size, 1280, 750);
    Ak::WindowComponent::setSetting(Ak::winsets::resizable, false);
}

void RectComponent::onEvent(Ak::Input& input)
{
    Ak::WindowComponent::onEvent(input);
}

void RectComponent::onRender()
{
    Ak::WindowComponent::onRender();
}

void RectComponent::onQuit()
{
    Ak::WindowComponent::onQuit();
}
