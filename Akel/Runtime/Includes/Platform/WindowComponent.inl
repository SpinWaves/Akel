// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/02/2024
// Updated : 09/02/2024

#pragma once
#include <Platform/WindowComponent.h>

namespace Ak
{
	void WindowComponent::OnFixedUpdate() noexcept
	{
		m_backend_window->UpdateWindowInfos();
	}

	std::size_t WindowComponent::GetWidth() const noexcept
	{
		return m_backend_window->GetWidth();
	}
	
	std::size_t WindowComponent::GetHeight() const noexcept
	{
		return m_backend_window->GetHeight();
	}
	
	void WindowComponent::SetPosition(const Vec2i& position) noexcept
	{
		m_backend_window->SetPosition(position);
	}
	
	void WindowComponent::SetPosition(std::uint32_t posx, std::uint32_t posy) noexcept
	{
		m_backend_window->SetPosition(posx, posy);
	}
	
	void WindowComponent::SetSize(const Vec2i& size) noexcept
	{
		m_backend_window->SetSize(size);
	}
	
	void WindowComponent::SetSize(std::uint32_t sizex, std::uint32_t sizey) noexcept
	{
		m_backend_window->SetSize(sizex, sizey);
	}
	
	void WindowComponent::SetMaxSize(const Vec2i& size) noexcept
	{
		m_backend_window->SetMaxSize(size);
	}
	
	void WindowComponent::SetMaxSize(std::uint32_t sizex, std::uint32_t sizey) noexcept
	{
		m_backend_window->SetMaxSize(sizex, sizey);
	}
	
	void WindowComponent::SetMinSize(const Vec2i& size) noexcept
	{
		m_backend_window->SetMinSize(size);
	}
	
	void WindowComponent::SetMinSize(std::uint32_t sizex, std::uint32_t sizey) noexcept
	{
		m_backend_window->SetMinSize(sizex, sizey);
	}
	
	void WindowComponent::SetTitle(const std::string& title)
	{
		m_backend_window->SetTitle(title);
	}
	
	const std::string& WindowComponent::GetTitle() const
	{
		return m_backend_window->GetTitle();
	}
	
	const Vec2i& WindowComponent::GetPosition() const noexcept
	{
		return m_backend_window->GetPosition();
	}
	
	const Vec2i& WindowComponent::GetSize() const noexcept
	{
		return m_backend_window->GetSize();
	}
	
	const Vec2i& WindowComponent::GetMinSize() const noexcept
	{
		return m_backend_window->GetMinSize();
	}

	const Vec2i& WindowComponent::GetMaxSize() const noexcept
	{
		return m_backend_window->GetMaxSize();
	}
}
