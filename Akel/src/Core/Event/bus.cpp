// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/06/2023
// Updated : 11/09/2023

#include <Core/Event/bus.h>
#include <Core/log.h>

namespace Ak
{
	void EventBus::send(const std::string& listener_name, const BaseEvent& event)
	{
		for(const EventListener& listener : _listeners)
		{
			if(listener.getName() == listener_name)
			{
				listener.call(event);
				return;
			}
		}
		Core::log::report(WARNING, "Event Bus : listener not found, '%s'", listener_name.c_str());
	}
}
