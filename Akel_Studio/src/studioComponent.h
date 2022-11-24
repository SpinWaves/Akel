// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 06/07/2021
// Updated : 24/11/2022

#ifndef __AK_STUDIO_COMPONENT__
#define __AK_STUDIO_COMPONENT__

#include <AkSpch.h>
#include <Panels/panels.h>

class StudioComponent : public Ak::WindowComponent
{
	public:
		StudioComponent();

		void onAttach() override;
		void onImGuiRender() override;
		void onImGuiEvent(Ak::Input& input) override;
		void onQuit() override;

		void generateFontTextures(Ak::ImGuiComponent* imgui);

		void setContext();
		inline void setCamera(class SceneCamera* camera) noexcept { _camera = camera; } 

		~StudioComponent() = default;

	private:
		void drawMainMenuBar();
		void drawAboutWindow();
		void drawOptionsWindow();
		void draw_general_settings();
		void draw_scene_settings();

		std::string _eltm_editor_input_buffer;
		std::shared_ptr<Ak::ELTM> _eltm;
		uint8_t _eltm_editor_save = 0;
		Ak::Unique_ptr<PanelStack> _stack;
		class SceneCamera* _camera = nullptr;
		std::array<bool, 1> _opts;
		bool _running = true;
		bool _showAbout = false;
		bool _showOpt = false;
};

#endif // __AK_STUDIO_COMPONENT__
