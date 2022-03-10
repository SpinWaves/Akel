// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 06/07/2021
// Updated : 10/03/2022

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
		void onImGuiEvent(Ak::Input& input) override;
		void onQuit() override;

		~EditorComponent() = default;

	private:
		void drawMainMenuBar();
		void drawAboutWindow();
		void drawOptionsWindow();

		bool _running = true;
		ImGuiID dockspaceID = 0;
		bool _showAbout = false;
		bool _showOpt = false;
		std::array<bool, 1> _opts;

		std::string _eltm_editor_input_buffer;

		std::shared_ptr<Ak::ELTM> _eltm;
		Ak::unique_ptr_w<PanelStack> _stack;
};

#endif // __AK_EDITOR_COMPONENT__
