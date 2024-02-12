// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2024
// Updated : 12/02/2024

#ifndef __AK_GLFW_WINDOW__
#define __AK_GLFW_WINDOW__

#include <Drivers/GLFW/PreCompiled.h>
#include <Platform/SI/Window.h>

namespace Ak
{
	class AK_GLFW_API GLFWWindow : public SIWindow
	{
		public:
			GLFWWindow(std::size_t width, std::size_t height, const std::string& title, WindowStyle style);

			void CreateWindow() override;
			void UpdateWindowInfos() noexcept override;

			void SetPosition(const Vec2i& position) noexcept override;
			void SetPosition(std::uint32_t posx, std::uint32_t posy) noexcept override;

			void SetSize(const Vec2i& size) noexcept override;
			void SetSize(std::uint32_t sizex, std::uint32_t sizey) noexcept override;

			void SetMaxSize(const Vec2i& size) noexcept override;
			void SetMaxSize(std::uint32_t sizex, std::uint32_t sizey) noexcept override;

			void SetMinSize(const Vec2i& size) noexcept override;
			void SetMinSize(std::uint32_t sizex, std::uint32_t sizey) noexcept override;

			void SetTitle(const std::string& title) override;

			~GLFWWindow();

		private:
			GLFWwindow* m_window = nullptr;
	};

}

#endif
