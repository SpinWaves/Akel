// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/02/2024
// Updated : 01/02/2024

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
