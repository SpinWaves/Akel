// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/02/2024
// Updated : 11/02/2024

#ifndef __AK_PLATFORM_WINDOW_COMPONENT__
#define __AK_PLATFORM_WINDOW_COMPONENT__

#include "Core/CompilationProfile.h"
#include <Platform/PreCompiled.h>
#include <Core/ComponentBase.h>
#include <Maths/Vec2.h>
#include <Platform/SI/Window.h>

namespace Ak
{
	class AK_PLATFORM_API WindowComponent : public ComponentBase
	{
		public:
			WindowComponent(std::size_t width, std::size_t height, std::uint32_t style = 0);
			WindowComponent(std::size_t width, std::size_t height, const std::string& title, std::uint32_t style = 0);

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

			~WindowComponent() = default;

		private:
			SIWindow* m_backend_window = nullptr;
	};
}

#include <Platform/WindowComponent.inl>

#endif
