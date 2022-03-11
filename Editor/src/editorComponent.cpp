// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 06/07/2021
// Updated : 11/03/2022

#include <editorComponent.h>

EditorComponent::EditorComponent() : Ak::WindowComponent()
{
	_eltm = Ak::create_shared_ptr_w<Ak::ELTM>(true);
}

void EditorComponent::onAttach()
{
	std::string language = "language";
	_eltm->load(Ak::Core::getMainDirPath() + "Editor/texts/langs.eltm");
	if(Ak::Core::ProjectFile::getStringValue(language) == "")
		Ak::Core::ProjectFile::setStringValue(language, _eltm->getLocalText("Languages.English"));
	_eltm->load(Ak::Core::getMainDirPath() + "Editor/texts/En/main.eltm");

	Ak::WindowComponent::onAttach();
	Ak::WindowComponent::title = _eltm->getLocalText("window_title");
	Ak::WindowComponent::resizable = true;
	Ak::WindowComponent::maximize = true;
	Ak::WindowComponent::fetchSettings();

	_stack = Ak::create_unique_ptr_w<PanelStack>();

	_stack->add_panel<Docks>(_eltm);
	_stack->add_panel<ELTM_editor>(_eltm->getLocalText("ELTM_Editor.name"), &_eltm_editor_input_buffer);
	_stack->add_panel<Entities>(_eltm);
	_stack->add_panel<EntitiesManager>(_eltm);
	_stack->add_panel<RendererManager>(_eltm);
	_stack->add_panel<AudioManager>(_eltm);
	_stack->add_panel<Materials>(_eltm);
	_stack->add_panel<MaterialEditor>(_eltm);
	_stack->add_panel<Browser>(_eltm);
	_stack->add_panel<Console>(_eltm);
}

void EditorComponent::onImGuiRender()
{
	drawMainMenuBar();

	for(auto elem : _stack->_panels)
		elem->onUpdate(size);

	if(_showAbout)
		drawAboutWindow();
	if(_showOpt)
		drawOptionsWindow();
}

void EditorComponent::onImGuiEvent(Ak::Input& input)
{
	Ak::WindowComponent::onEvent(input);
	if(!_running)
		input.finish();

	for(auto elem : _stack->_panels)
		elem->onEvent(input);
	
	_eltm_editor_input_buffer.clear();
}

void EditorComponent::onQuit()
{
	for(auto elem : _stack->_panels)
		elem->onQuit();
	_stack.reset(nullptr);
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
			if(ImGui::MenuItem(_eltm->getLocalText("ELTM_Editor.name").c_str()))
				_stack->get_panel("__eltm_editor")->onOpen();
			ImGui::EndMenu();
		}
		if(_stack->get_panel("__eltm_editor")->isOpen() && ImGui::BeginMenu(_eltm->getLocalText("MainMenuBar.eltm_editor").c_str()))
		{
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.e_load").c_str()))
			{
				auto file = pfd::open_file(_eltm->getLocalText("MainMenuBar.e_load"), Ak::Core::getMainDirPath(), { "ELTM files (.eltm .tm)", "*.eltm *.tm", "All files", "*"});	
				if(!file.result().empty())
					_eltm_editor_input_buffer = file.result()[0];
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
		ImGui::SameLine(size.X - 100);
		ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);

		ImGui::EndMainMenuBar();
	}
}

void EditorComponent::drawAboutWindow()
{
	if(ImGui::Begin(_eltm->getLocalText("MainMenuBar.about").data(), &_showAbout, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
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
