// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Graphics/Renderer/RenderingSurfaceComponent.h>
#include <Platform/WindowComponent.h>
#include <Graphics/GraphicsModule.h>
#include <Graphics/RHI/RHIDevice.h>

namespace Ak
{
	RenderingSurfaceComponent::RenderingSurfaceComponent(WindowComponent& window, std::uint32_t device) : ComponentBase("__RenderingSurface"), m_window(window), m_device(device)
	{
	}

	void RenderingSurfaceComponent::OnAttach() noexcept
	{
	}

	void RenderingSurfaceComponent::OnQuit() noexcept
	{
	}
}
