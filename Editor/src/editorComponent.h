// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 06/07/2021
// Updated : 07/03/2022

#ifndef __AK_EDITOR_COMPONENT__
#define __AK_EDITOR_COMPONENT__

#include <AkEpch.h>
#include <Panels/panels.h>

class EditorComponent : public Ak::WindowComponent
{
	public:
		EditorComponent();

		void onAttach() override;
		void onImGuiRender() override;
		void onEvent(Ak::Input& input) override;
		void onQuit() override;

		~EditorComponent() = default;

	private:
		void drawMainMenuBar();
		void drawAboutWindow();
		void drawOptionsWindow();

		bool _running = true;
		ImGuiID dockspaceID = 0;
		std::shared_ptr<Ak::ELTM> _eltm;
		Ak::unique_ptr_w<Console> _console;
		Ak::unique_ptr_w<ELTM_editor> _eltm_editor;
		bool _showAbout = false;
		bool _showOpt = false;
		std::array<bool, 1> _opts;
};

#endif // __AK_EDITOR_COMPONENT__
