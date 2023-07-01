// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/06/2023
// Updated : 01/07/2023

#ifndef __AK_EVENT_LISTENER__
#define __AK_EVENT_LISTENER__

#include <Akpch.h>
#include <Core/Event/base_event.h>

namespace Ak
{
	class AK_API EventListener
	{
		public:
			EventListener() = delete;
			EventListener(func::function<void(const BaseEvent&)> functor, std::string name);

			inline const std::string& getName() const { return _name; }
			inline void call(const BaseEvent& event) const noexcept { _listen_functor(event); }

			~EventListener() = default;

		private:
			func::function<void(const BaseEvent&)> _listen_functor;
			std::string _name;
	};
}

#endif
