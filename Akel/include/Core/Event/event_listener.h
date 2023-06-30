// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/06/2023
// Updated : 30/06/2023

#ifndef __AK_EVENT_LISTENER__
#define __AK_EVENT_LISTENER__

#include <Akpch.h>
#include <Core/Event/base_event.h>

namespace Ak
{
	template <typename F>
	class EventListener
	{
		public:
			EventListener() = delete;
			EventListener(F&& functor);

			inline const std::string& getName() const { return _name; }
			inline void call(const BaseEvent& event) noexcept { _listen_functor(event); }

			~EventListener() = default;

		private:
			F _listen_functor;
			std::string _name;
	};

	template <typename F>
	EventListener(F) -> EventListener<F>;
}

#endif
