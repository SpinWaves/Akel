#include "comp.h"

Comp::Comp() : Ak::Component() {}

void Comp::onAttach()
{
    std::cout << "Running..." << std::endl;
}

void Comp::onEvent(Ak::Input& input)
{
    input.finish();
}

void Comp::update() {}

void Comp::onQuit()
{
    std::cout << "End" << std::endl;
}
