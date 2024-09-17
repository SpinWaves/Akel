// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_CORE_EVENT_LISTENER__
#define __AK_CORE_EVENT_LISTENER__

#include <Core/PreCompiled.h>
#include <Core/EventBase.h>

namespace Ak
{
	class AK_CORE_API EventListener
	{
		public:
			EventListener() = delete;
			EventListener(func::function<void(const EventBase&)> functor, std::string name);

			inline const std::string& GetName() const { return m_name; }
			inline void Call(const EventBase& event) const noexcept { m_listen_functor(event); }

			~EventListener() = default;

		private:
			func::function<void(const EventBase&)> m_listen_functor;
			std::string m_name;
	};
}

#endif
