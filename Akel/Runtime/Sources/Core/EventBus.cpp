// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

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
