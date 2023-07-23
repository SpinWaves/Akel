// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/06/2021
// Updated : 24/07/2023

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
	void Component::onImGuiEvent(Input& input) {}
	void Component::onEvent(Input& input) {}
	void Component::onQuit() {}

	Component::~Component() {}
}

