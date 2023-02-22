// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 22/02/2023
// Updated : 22/02/2023

#ifndef __AK_STUDIO_LAUNCHER_COMPONENT__
#define __AK_STUDIO_LAUNCHER_COMPONENT__

#include <Akel.h>
#include <Fonts/material_font.h>

class LauncherComponent : public Ak::Component
{
	public:
		LauncherComponent() = default;

		void onAttach() override;
		void onImGuiRender() override;
		void onImGuiEvent(Ak::Input& input) override;
		void onQuit() override;

		void generateFontTextures(Ak::ImGuiComponent* imgui);

		~LauncherComponent() = default;

	private:
		void drawMainContent();
		void drawSideBar();

		AkImGui::ImImage _logo;
		ImFont* _tiny_font = nullptr;
		ImFont* _title_font = nullptr;
};

#endif
