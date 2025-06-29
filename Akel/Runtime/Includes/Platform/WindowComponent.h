// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_PLATFORM_WINDOW_COMPONENT_H
#define AK_PLATFORM_WINDOW_COMPONENT_H

#include <Platform/PreCompiled.h>
#include <Core/ComponentBase.h>
#include <Maths/Vec2.h>
#include <Platform/SI/Window.h>
#include <Utils/NonOwningPtr.h>

namespace Ak
{
	class AK_PLATFORM_API WindowComponent : public ComponentBase
	{
		public:
			WindowComponent(std::size_t width, std::size_t height, WindowStyle style = 0);
			WindowComponent(std::size_t width, std::size_t height, const std::string& title, WindowStyle style = 0);

			void OnAttach() noexcept override;
			AK_FORCEINLINE void OnFixedUpdate() noexcept override;
			void OnQuit() noexcept override;

			AK_FORCEINLINE std::size_t GetWidth() const noexcept;
			AK_FORCEINLINE std::size_t GetHeight() const noexcept;
			AK_FORCEINLINE void SetPosition(const Vec2i& position) noexcept;
			AK_FORCEINLINE void SetPosition(std::uint32_t posx, std::uint32_t posy) noexcept;
			AK_FORCEINLINE void SetSize(const Vec2i& size) noexcept;
			AK_FORCEINLINE void SetSize(std::uint32_t sizex, std::uint32_t sizey) noexcept;
			AK_FORCEINLINE void SetMaxSize(const Vec2i& size) noexcept;
			AK_FORCEINLINE void SetMaxSize(std::uint32_t sizex, std::uint32_t sizey) noexcept;
			AK_FORCEINLINE void SetMinSize(const Vec2i& size) noexcept;
			AK_FORCEINLINE void SetMinSize(std::uint32_t sizex, std::uint32_t sizey) noexcept;
			AK_FORCEINLINE void SetTitle(const std::string& title);
			AK_FORCEINLINE const std::string& GetTitle() const;
			AK_FORCEINLINE const Vec2i& GetPosition() const noexcept;
			AK_FORCEINLINE const Vec2i& GetSize() const noexcept;
			AK_FORCEINLINE const Vec2i& GetMinSize() const noexcept;
			AK_FORCEINLINE const Vec2i& GetMaxSize() const noexcept;
			AK_FORCEINLINE NonOwningPtr<SIWindow> GetRawWindow() const noexcept { return p_backend_window.Get(); }

			~WindowComponent() = default;

		private:
			UniquePtr<SIWindow> p_backend_window = nullptr;
	};
}

#include <Platform/WindowComponent.inl>

#endif
