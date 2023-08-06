// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/06/2021
// Updated : 06/08/2023

#include <Core/Components/baseComponent.h>
#include <Core/projectFile.h>

namespace Ak
{
	Component::Component(std::string name) : _name(std::move(name))
	{
		getMainAppProjectFile().archive()[_name] = true;
	}

	void Component::onAttach() {}
	void Component::onUpdate(float delta) {}
	void Component::onFixedUpdate() {}
	void Component::onRender() {}
	void Component::onEvent(Input& input) {}
	void Component::onQuit() {}

	Component::~Component() {}
}

