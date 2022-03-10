// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 10/03/2022

#include <Panels/Base/panel.h>

Panel::Panel(const char* name)
{
	_name = name;
}

void Panel::onAttach() {}
void Panel::onOpen() {}
bool Panel::isOpen() {}
void Panel::onUpdate(Ak::Maths::Vec2<int>& size) {}
void Panel::onEvent(Ak::Input& input) {}
void Panel::onQuit() {}

Panel::~Panel() {}
