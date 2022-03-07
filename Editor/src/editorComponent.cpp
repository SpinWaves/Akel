// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 06/07/2021
// Updated : 07/03/2022

#include <editorComponent.h>

EditorComponent::EditorComponent() : Ak::WindowComponent()
{
	_eltm = Ak::make_shared_ptr_w<Ak::ELTM>(Ak::memAlloc<Ak::ELTM>(true));
}

void EditorComponent::onAttach()
{
	Ak::WindowComponent::onAttach();
	Ak::WindowComponent::setSetting(Ak::winsets::title, "Akel Editor");
	Ak::WindowComponent::setSetting(Ak::winsets::resizable, true);
	Ak::WindowComponent::setSetting(Ak::winsets::size, AK_WINDOW_MAX_SIZE, AK_WINDOW_MAX_SIZE);
	Ak::WindowComponent::setSetting(Ak::winsets::maximize, true);

	std::string language = "language";
	_eltm->load(Ak::Core::getMainDirPath() + "Editor/texts/langs.eltm");
	if(Ak::Core::ProjectFile::getStringValue(language) == "")
		Ak::Core::ProjectFile::setStringValue(language, _eltm->getLocalText("Languages.English"));

	_eltm->load(Ak::Core::getMainDirPath() + "Editor/texts/Fr/main.eltm");
	_console = Ak::make_unique_ptr_w<Console>(Ak::memAlloc<Console>(_eltm->getLocalText("Console.name"), _eltm));
	_eltm_editor = Ak::make_unique_ptr_w<ELTM_editor>(Ak::memAlloc<ELTM_editor>(_eltm->getLocalText("ELTM_Editor.name")));
}

void EditorComponent::onImGuiRender()
{
	drawMainMenuBar();
	_console->render(WindowComponent::getSize().X, WindowComponent::getSize().Y);
	_eltm_editor->render(WindowComponent::getSize().X, WindowComponent::getSize().Y);
	if(_showAbout)
		drawAboutWindow();
	if(_showOpt)
		drawOptionsWindow();
}

void EditorComponent::onEvent(Ak::Input& input)
{
	Ak::WindowComponent::onEvent(input);
	if(!_running || _console->_sh.quit())
		input.finish();
}

void EditorComponent::onQuit()
{
	Ak::WindowComponent::onQuit();
}

void EditorComponent::drawMainMenuBar()
{
	if(ImGui::BeginMainMenuBar())
	{
		if(ImGui::BeginMenu(_eltm->getLocalText("MainMenuBar.file").c_str()))
		{
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.open").c_str(), "Ctrl+O"))
			{
				auto file = pfd::open_file(_eltm->getLocalText("MainMenuBar.open"), Ak::Core::getMainDirPath(), { "Akel projects (.akel)", "*.akel" });	
			}
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.save").c_str(), "Ctrl+S")) { /* Do stuff */ }
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.quit").c_str()))
				_running = false;
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu(_eltm->getLocalText("MainMenuBar.edit").c_str()))
		{
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.addFile").c_str())) { /* Do stuff */ }
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.build").c_str()))   { /* Do stuff */ }
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.options").c_str()))
				_showOpt = _showOpt ? false : true;
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu(_eltm->getLocalText("MainMenuBar.panels").c_str()))
		{
			if(ImGui::MenuItem(_eltm->getLocalText("Console.name").c_str()))
				_console->open();
			if(ImGui::MenuItem(_eltm->getLocalText("ELTM_Editor.name").c_str()))
				_eltm_editor->open();
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu(_eltm->getLocalText("MainMenuBar.eltm_editor").c_str()))
		{
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.e_load").c_str()))
			{
				auto file = pfd::open_file(_eltm->getLocalText("MainMenuBar.e_load"), Ak::Core::getMainDirPath(), { "ELTM files (.eltm .tm)", "*.eltm *.tm", "All files", "*"});	
				if(!file.result().empty())
					_eltm_editor->load(file.result()[0]);
			}
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.e_save").c_str()))
			{
			}
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.e_save_as").c_str()))
			{
				
			}
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu(_eltm->getLocalText("MainMenuBar.help").c_str()))
		{
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.about").c_str()))
				_showAbout = _showAbout ? false : true;
			ImGui::EndMenu();
		}
		ImGui::SameLine(ImGui::GetColumnWidth(-1));
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);

		ImGui::EndMainMenuBar();
	}
}

void EditorComponent::drawAboutWindow()
{
	if(ImGui::Begin(_eltm->getLocalText("MainMenuBar.about").data(), &_showAbout, ImGuiWindowFlags_NoResize))
	{
		ImGui::TextUnformatted(_eltm->getLocalText("MainMenuBar.version").data());
		ImGui::End();
	}
}

void EditorComponent::drawOptionsWindow()
{
	if(ImGui::Begin(_eltm->getLocalText("MainMenuBar.options").data(), &_showOpt))
	{
		static int selected = -1;
		
		ImGui::SetWindowSize(ImVec2(800, 800), ImGuiCond_FirstUseEver);
  
    	if(ImGui::BeginChild("Panel", ImVec2(100, 750), true))
		{
			if(ImGui::Selectable(_eltm->getLocalText("lang").data(), selected == 0))
				selected = 0;
			if(ImGui::Selectable("test", selected == 1))
				selected = 1;
			ImGui::EndChild();
		}
		
		if(ImGui::BeginChild("Choices", ImVec2(700, 750), true))
		{
			ImGui::Button(_eltm->getLocalText("lang").data(), ImVec2(85, 25));
			ImGui::EndChild();
		}

		ImGui::End();
	}	
}
