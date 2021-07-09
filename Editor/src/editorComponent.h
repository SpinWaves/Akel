// This file is a part of the Akel editor
// CREATED : 06/07/2021
// UPDATED : 09/07/2021

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
		void dockSpace();

		bool _running = true;
		ImGuiID dockspaceID = 0;
		std::shared_ptr<Ak::ELTMcontext> _eltm;
		std::shared_ptr<Console> _console;
};

#endif // __AK_EDITOR_COMPONENT__

