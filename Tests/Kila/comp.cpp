#include "comp.h"

Comp::Comp() : Ak::Component("Kila tester component") {}

void Comp::onAttach()
{
    std::cout << "Running..." << std::endl;
}

void Comp::onEvent(Ak::Input& input)
{
    input.finish();
}

void Comp::update()
{
	Ak::Kl::Compiler kila_cpl;
	kila_cpl.generateSpirVFromFile(std::string(Ak::Core::getMainDirPath() + "test.ksl"));
}

void Comp::onQuit()
{
    std::cout << "End" << std::endl;
}
