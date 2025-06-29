// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Graphics/Renderer/RenderingSurfaceComponent.h>
#include <Platform/WindowComponent.h>
#include <Graphics/GraphicsModule.h>
#include <Graphics/RHI/RHIDevice.h>
#include <Graphics/Renderer/RenderCore.h>
#include <Graphics/GraphicsModule.h>
#include <Graphics/RHI/RHISwapchain.h>
#include <Graphics/RHI/RHISurface.h>

namespace Ak
{
	RenderingSurfaceComponent::RenderingSurfaceComponent(WindowComponent& window) : ComponentBase("__RenderingSurface"), m_window(window)
	{
	}

	void RenderingSurfaceComponent::OnAttach() noexcept
	{
		p_surface = GraphicsModule::Get().GetRenderCore().GetInstance().CreateSurface(m_window);
		//p_swapchain = GraphicsModule::Get().GetRenderCore().GetDevice().CreateSwapchain(p_surface, Vec2ui(window.GetSize()), false, true);
	}

	void RenderingSurfaceComponent::OnQuit() noexcept
	{
		p_surface.Reset();
	}
}
