#include "cubeComponent.h"

CubeComponent::CubeComponent() : Ak::WindowComponent() {}

void CubeComponent::onAttach()
{
    Ak::WindowComponent::onAttach();
    Ak::WindowComponent::setSetting(ak::winsets::title, "Cube demo using Akel Engine");
    Ak::WindowComponent::setSetting(Ak:::winsets::size, 1280, 750);
    Ak::WindowComponent::setSetting(ak::winsets::resizable, false);
}

void CubeComponent::onEvent(Ak::Input& input)
{
    Ak::WindowComponent::onEvent(input);
}

void CubeComponent::update()
{
    Ak::WindowComponent::update();
}

void CubeComponent::onQuit()
{
    Ak::WindowComponent::onQuit();
}
