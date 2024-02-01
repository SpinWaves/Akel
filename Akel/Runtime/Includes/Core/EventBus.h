// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/02/2024
// Updated : 01/02/2024

#ifndef __AK_CORE_EVENT_BUS__
#define __AK_CORE_EVENT_BUS__

#include <Core/PreCompiled.h>
#include <Core/EventBase.h>
#include <Core/EventListener.h>

namespace Ak
{
	class AK_CORE_API EventBus
	{
		public:
			EventBus() = delete;
			static void Send(const std::string& listener_name, const EventBase& event);
			inline static void RegisterListener(const EventListener& listener) { s_listeners.push_back(listener); }
			~EventBus() = delete;

		private:
			inline static std::vector<EventListener> s_listeners;
	};
}

#endif
