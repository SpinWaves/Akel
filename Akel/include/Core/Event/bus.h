// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/06/2023
// Updated : 30/06/2023

#ifndef __AK_EVENT_BUS__
#define __AK_EVENT_BUS__

#include <Akpch.h>
#include <Core/Event/event_listener.h>

namespace Ak
{
	class EventBus
	{
		public:
			EventBus() = delete;
			static void send(const std::string& listener_name, const BaseEvent& event);
			~EventBus() = delete;

		private:
			inline static std::vector<EventListener> _listeners;
	};
}

#endif
