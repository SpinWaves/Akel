// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 06/07/2021
// Updated : 24/07/2023

#ifndef __AK_STUDIO_COMPONENT__
#define __AK_STUDIO_COMPONENT__

#include <AkSpch.h>
#include <Panels/panels.h>

class StudioComponent : public Ak::Component
{
	public:
		StudioComponent(Ak::CommandLineArgs args);

		void onAttach() override;
		void onFixedUpdate() override;
		void onRender() override;
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
		void draw_project_settings();
		void writeRuntimeSettings();
		void buildProject();

	private:
		Ak::Core::ProjectFile _project;
		nlohmann::json _runtime_settings;
		AkImGui::ImImage _logo;
		std::string _eltm_editor_input_buffer;
		std::shared_ptr<Ak::ELTM> _eltm;
		Ak::Unique_ptr<PanelStack> _stack;
		uint64_t _build_timer = 0;
		uint8_t _eltm_editor_save = 0;
		bool _running = true;
		bool _showAbout = false;
		bool _showOpt = false;
		bool _open_build = false;
};

#endif // __AK_STUDIO_COMPONENT__
