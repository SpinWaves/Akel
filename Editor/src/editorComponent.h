// This file is a part of the Akel editor
// CREATED : 06/07/2021
// UPDATED : 06/07/2021

#ifndef __AK_EDITOR_COMPONENT__
#define __AK_EDITOR_COMPONENT__

#include <AkEpch.h>

class EditorComponent : public Ak::ImGuiComponent
{
	public :
		EditorComponent();

		void onAttach() override;
		void onImGuiRender() override;
		void onQuit() override;

		~EditorComponent() = default;

	private :
};

#endif // __AK_EDITOR_COMPONENT__

