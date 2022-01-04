// This file is a part of Akel
// CREATED : 23/06/2021
// UPDATED : 04/01/2022

#include <Core/Components/baseComponent.h>

namespace Ak
{
	Component::Component(const char* name)
	{
		_name = name;
	}

	void Component::onAttach() {}
	void Component::update() {}
	void Component::onRender() {}
	void Component::onImGuiRender() {}
	void Component::onEvent(Input& input) {}
	void Component::onQuit() {}

	Component::~Component() {}
}

