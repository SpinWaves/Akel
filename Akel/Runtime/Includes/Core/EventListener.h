// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_EVENT_LISTENER_H
#define AK_CORE_EVENT_LISTENER_H

#include <Core/PreCompiled.h>

namespace Ak
{
	class AK_CORE_API EventListener
	{
		public:
			EventListener() = delete;
			EventListener(func::function<void(Event)> functor, std::string name);

			inline const std::string& GetName() const { return m_name; }
			inline void Call(Event event) const noexcept { m_listen_functor(event); }

			~EventListener() = default;

		private:
			func::function<void(Event)> m_listen_functor;
			std::string m_name;
	};
}

#endif
