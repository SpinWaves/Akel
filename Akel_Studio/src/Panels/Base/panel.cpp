// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 05/02/2023

#include <Panels/Base/panel.h>

Panel::Panel(const char* name)
{
	_name = name;
}

void Panel::onAttach() {}
void Panel::onOpen() {}
bool Panel::isOpen() { return false; }
void Panel::onUpdate(Ak::Maths::Vec2<int>& size) {}
void Panel::onEvent(Ak::Input& input) {}
void Panel::onQuit() {}

Panel::~Panel() {}
