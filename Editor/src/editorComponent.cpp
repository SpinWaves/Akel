// This file is a part of the Akel editor
// CREATED : 06/07/2021
// UPDATED : 24/07/2021

#include <editorComponent.h>

EditorComponent::EditorComponent() : Ak::ImGuiComponent("Akel Editor")
{
	_eltm = Ak::shared_ptr_w<Ak::ELTMcontext>(Ak::custom_malloc<Ak::ELTMcontext>());
	std::cout << "eltm" << sizeof(Ak::ELTMcontext) << std::endl;
}

void EditorComponent::onAttach()
{
	Ak::ImGuiComponent::onAttach();
	_eltm->newContext(Ak::Core::getMainDirPath() + "Editor/texts/En/main.eltm");
	_console = std::shared_ptr<Console>(new Console(_eltm->getText("Console.name")));
	std::cout << "console" << sizeof(Console) << std::endl;
}

void EditorComponent::onImGuiRender()
{
	drawMainMenuBar();
	_console->render(Window::getSize().X, Window::getSize().Y);
}

void EditorComponent::onEvent(Ak::Input& input)
{
	Ak::ImGuiComponent::onEvent(input);
	if(!_running || _console->_sh.quit())
		input.finish();
}

void EditorComponent::onQuit()
{
	Ak::ImGuiComponent::onQuit();
}

void EditorComponent::drawMainMenuBar()
{
	if(ImGui::BeginMainMenuBar())
	{
		if(ImGui::BeginMenu(_eltm->getText("MainMenuBar.file").c_str()))
		{
			if(ImGui::MenuItem(_eltm->getText("MainMenuBar.open").c_str(), "Ctrl+O")) { /* Do stuff */ }
			if(ImGui::MenuItem(_eltm->getText("MainMenuBar.save").c_str(), "Ctrl+S")) { /* Do stuff */ }
			if(ImGui::MenuItem(_eltm->getText("MainMenuBar.quit").c_str()))
				_running = false;
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu(_eltm->getText("MainMenuBar.edit").c_str()))
		{
			if(ImGui::MenuItem(_eltm->getText("MainMenuBar.addFile").c_str())) { /* Do stuff */ }
			if(ImGui::MenuItem(_eltm->getText("MainMenuBar.build").c_str()))   { /* Do stuff */ }
			ImGui::EndMenu();
		}
		ImGui::SameLine(ImGui::GetColumnWidth(-1));
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);

		ImGui::EndMainMenuBar();
	}
}
