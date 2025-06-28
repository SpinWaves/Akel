// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RENDERER_RENDERING_SURFACE_H
#define AK_RENDERER_RENDERING_SURFACE_H

#include <Graphics/PreCompiled.h>
#include <Core/ComponentBase.h>
#include <Utils/NonOwningPtr.h>

namespace Ak
{
	class AK_GRAPHICS_API RenderingSurfaceComponent : public ComponentBase
	{
		public:
			RenderingSurfaceComponent(class WindowComponent& window);

			void OnAttach() noexcept override;
			void OnQuit() noexcept override;

			~RenderingSurfaceComponent() = default;

		private:
			SharedPtr<class RHISurface> p_surface = nullptr;
			SharedPtr<class RHISwapchain> p_swapchain = nullptr;
			class WindowComponent& m_window;
	};
}

#endif
