// This file is a part of the Akel editor
// CREATED : 08/06/2021
// UPDATED : 06/07/2021

#ifndef __AK_EDITOR_APP__
#define __AK_EDITOR_APP__

#include <AkEpch.h>
#include <Akel_main.h>
#include <editorComponent.h>

class Editor : public Ak::Application
{
	public:
		Editor() : Ak::Application("Akel Editor")
		{
			add_component(new EditorComponent);
		}
		~Editor() = default;
};

Ak::Application* Akel_main()
{
	return new Editor;
}

#endif // __AK_EDITOR_APP__

