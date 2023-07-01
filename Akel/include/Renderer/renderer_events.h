// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/07/2023
// Updated : 02/07/2023

#ifndef __AK_RENDERER_EVENTS__
#define __AK_RENDERER_EVENTS__

#include <Core/Event/base_event.h>

namespace Ak
{
	enum class RenderEvents
	{
		resized = 0,
		quit = 1,
	};

	class ResizeEvent : public BaseEvent
	{
		public:
			ResizeEvent() = default;
			uint32_t what() const override { return static_cast<uint32_t>(RenderEvents::resized); }
			~ResizeEvent() = default;
	};

	class RenderQuitEvent : public BaseEvent
	{
		public:
			RenderQuitEvent() = default;
			uint32_t what() const override { return static_cast<uint32_t>(RenderEvents::quit); }
			~RenderQuitEvent() = default;
	};
}

#endif
