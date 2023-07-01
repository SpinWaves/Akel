// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/07/2023
// Updated : 01/07/2023

#include <Core/Event/event_listener.h>

namespace Ak
{
	EventListener::EventListener(func::function<void(const BaseEvent&)> functor, std::string name)
	: _listen_functor(std::move(functor)), _name(std::move(name))
	{}
}
