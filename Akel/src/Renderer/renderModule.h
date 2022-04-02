// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/03/2022
// Updated : 02/04/2022

#ifndef __AK_VK_RENDER_MODULE__
#define __AK_VK_RENDER_MODULE__

#include <Akpch.h>

namespace Ak
{
	class RenderModule
	{
		public:
			explicit RenderModule(const char* name, const WindowComponent* window) : _name(name), _window(window) {}

			virtual void render(const class CommandBuffer &commandBuffer) = 0;

			inline constexpr void enable() noexcept { _enabled = true; }
			inline constexpr void disable() noexcept { _enabled = false; }
			inline bool isEnabled() const noexcept { return _enabled; }
			inline const char* getName() const noexcept { return _name; }
			inline void setName(const char* name) noexcept { _name = name; }
			inline const WindowComponent* getWindow() const noexcept { return _window; }

			virtual ~RenderModule() = default;

		private:
			bool _enabled = true;
			const char* _name = nullptr;
			const WindowComponent* _window = nullptr;
	};
}

#endif // __AK_VK_RENDER_MODULE__
