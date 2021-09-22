#include "rectComponent.h"

RectComponent::RectComponent() : Ak::Window() {}

void RectComponent::onAttach()
{
    Ak::Window::create();
    Ak::Window::setSetting<title>("Rectangle using Akel Engine");
    Ak::Window::setSetting<dimensions>(1280, 750);
    Ak::Window::setSetting<resizable>(false);
}

void RectComponent::onEvent(Ak::Input& input)
{
    Ak::Window::onEvent(input);
}

void RectComponent::update()
{
    Ak::Window::update();
}

void RectComponent::onQuit()
{
    Ak::Window::onQuit();
}
