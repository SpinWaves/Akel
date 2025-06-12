// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_EVENT_BUS_H
#define AK_CORE_EVENT_BUS_H

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
