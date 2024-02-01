// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/02/2024
// Updated : 02/02/2024

#include <Core/EventBus.h>
#include <Core/Logs.h>

namespace Ak
{
	void EventBus::Send(const std::string& listener_name, const EventBase& event)
	{
		for(const EventListener& listener : s_listeners)
		{
			if(listener.GetName() == listener_name)
			{
				listener.Call(event);
				return;
			}
		}
		Warning("Event Bus : listener not found, '%'", listener_name);
	}
}
