// This file is a part of the Akel editor
// CREATED : 06/07/2021
// UPDATED : 10/09/2021

#ifndef __AK_EDITOR_COMPONENT__
#define __AK_EDITOR_COMPONENT__

#include <AkEpch.h>
#include <Panels/panels.h>

class EditorComponent : public Ak::ImGuiComponent
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

		bool _running = true;
		ImGuiID dockspaceID = 0;
		Ak::unique_ptr_w<Ak::ELTM> _eltm;
		Ak::unique_ptr_w<Console> _console;
		bool _showAbout = false;
};

#endif // __AK_EDITOR_COMPONENT__
