// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/06/2023
// Updated : 03/06/2023

#ifndef __AK_FPS__
#define __AK_FPS__

#include <Akpch.h>

namespace Ak
{
	class AK_API CounterFPS
	{
		friend class RendererComponent;

		public:
			CounterFPS() = default;
			inline bool makeRendering() const noexcept { return _make_render; }
			inline void setMaxFPS(uint32_t fps) noexcept { _max_fps = fps; _ns = 1000000000.0 / fps; }
			inline uint32_t getFPS() const noexcept { return _output_fps; }
			~CounterFPS() = default;

		private:
			void init();
			void update();

		private:
			double _ns = 1000000000.0 / 100'000.0;
			uint64_t _timer = 0;
			uint64_t _fps_before = 0;
			uint64_t _fps_now = 0;
			uint32_t _max_fps = 100'000;
			uint32_t _fps_elapsed_time = 0;
			uint32_t _fps = 0;
			uint32_t _output_fps = 0;
			bool _make_render = false;
	};
}

#endif
