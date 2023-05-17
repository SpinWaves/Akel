// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 06/07/2021
// Updated : 17/05/2023

#ifndef __AK_STUDIO_COMPONENT__
#define __AK_STUDIO_COMPONENT__

#include <AkSpch.h>
#include <Panels/panels.h>

class StudioComponent : public Ak::Component
{
	public:
		StudioComponent(Ak::CommandLineArgs args);

		void onAttach() override;
		void onImGuiRender() override;
		void onImGuiEvent(Ak::Input& input) override;
		void onQuit() override;

		void generateFontTextures(Ak::ImGuiComponent* imgui);

		~StudioComponent() = default;

	private:
		void drawMainMenuBar();
		void drawAboutWindow();
		void drawOptionsWindow();
		void draw_general_settings();
		void draw_scene_settings();

	private:
		Ak::Core::ProjectFile _project;
		AkImGui::ImImage _logo;
		std::string _eltm_editor_input_buffer;
		std::shared_ptr<Ak::ELTM> _eltm;
		class SceneCamera* _camera = nullptr;
		Ak::Unique_ptr<PanelStack> _stack;
		uint8_t _eltm_editor_save = 0;
		bool _running = true;
		bool _showAbout = false;
		bool _showOpt = false;
};

#endif // __AK_STUDIO_COMPONENT__
