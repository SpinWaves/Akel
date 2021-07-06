// This file is a part of the Akel editor
// CREATED : 06/07/2021
// UPDATED : 06/07/2021

#include <editorComponent.h>

EditorComponent::EditorComponent() : Ak::ImGuiComponent("Akel Editor") {}

void EditorComponent::onAttach()
{
	Ak::ImGuiComponent::onAttach();
}
void EditorComponent::onImGuiRender()
{
	if(ImGui::BeginMenuBar())
	{
		if(ImGui::BeginMenu("File"))
		{
			if(ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if(ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
			if(ImGui::MenuItem("Close", "Ctrl+W"))  {}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Text("Hello, world %d", 123);
	if(ImGui::Button("Save"))
		std::cout << "oui" << std::endl;
	//ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
	float f = 0.0f;
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
}
void EditorComponent::onQuit()
{
	Ak::ImGuiComponent::onQuit();
}

