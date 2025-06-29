// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once
#include <Platform/WindowComponent.h>

namespace Ak
{
	void WindowComponent::OnFixedUpdate() noexcept
	{
		p_backend_window->UpdateWindowInfos();
	}

	std::size_t WindowComponent::GetWidth() const noexcept
	{
		return p_backend_window->GetWidth();
	}
	
	std::size_t WindowComponent::GetHeight() const noexcept
	{
		return p_backend_window->GetHeight();
	}
	
	void WindowComponent::SetPosition(const Vec2i& position) noexcept
	{
		p_backend_window->SetPosition(position);
	}
	
	void WindowComponent::SetPosition(std::uint32_t posx, std::uint32_t posy) noexcept
	{
		p_backend_window->SetPosition(posx, posy);
	}
	
	void WindowComponent::SetSize(const Vec2i& size) noexcept
	{
		p_backend_window->SetSize(size);
	}
	
	void WindowComponent::SetSize(std::uint32_t sizex, std::uint32_t sizey) noexcept
	{
		p_backend_window->SetSize(sizex, sizey);
	}
	
	void WindowComponent::SetMaxSize(const Vec2i& size) noexcept
	{
		p_backend_window->SetMaxSize(size);
	}
	
	void WindowComponent::SetMaxSize(std::uint32_t sizex, std::uint32_t sizey) noexcept
	{
		p_backend_window->SetMaxSize(sizex, sizey);
	}
	
	void WindowComponent::SetMinSize(const Vec2i& size) noexcept
	{
		p_backend_window->SetMinSize(size);
	}
	
	void WindowComponent::SetMinSize(std::uint32_t sizex, std::uint32_t sizey) noexcept
	{
		p_backend_window->SetMinSize(sizex, sizey);
	}
	
	void WindowComponent::SetTitle(const std::string& title)
	{
		p_backend_window->SetTitle(title);
	}
	
	const std::string& WindowComponent::GetTitle() const
	{
		return p_backend_window->GetTitle();
	}
	
	const Vec2i& WindowComponent::GetPosition() const noexcept
	{
		return p_backend_window->GetPosition();
	}
	
	const Vec2i& WindowComponent::GetSize() const noexcept
	{
		return p_backend_window->GetSize();
	}
	
	const Vec2i& WindowComponent::GetMinSize() const noexcept
	{
		return p_backend_window->GetMinSize();
	}

	const Vec2i& WindowComponent::GetMaxSize() const noexcept
	{
		return p_backend_window->GetMaxSize();
	}
}
