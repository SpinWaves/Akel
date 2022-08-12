// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 06/07/2021
// Updated : 13/08/2022

#include <studioComponent.h>

Ak::Unique_ptr<Ak::ELTM> _lang_eltm(nullptr);

StudioComponent::StudioComponent() : Ak::WindowComponent(), _eltm(Ak::create_shared_ptr_w<Ak::ELTM>(false)) {}

void StudioComponent::onAttach()
{
	_lang_eltm = Ak::create_Unique_ptr<Ak::ELTM>(false);
	_lang_eltm->load(Ak::Core::getMainDirPath() + "../../texts/langs.eltm");

	if(!Ak::Core::ProjectFile::keyExists("language"))
		Ak::Core::ProjectFile::setStringValue("language", Ak::Core::getMainDirPath() + _lang_eltm->getLocalText("English"));
	if(!Ak::Core::ProjectFile::keyExists("on_quit_window"))
		Ak::Core::ProjectFile::setBoolValue("on_quit_window", true);
	if(!Ak::Core::ProjectFile::keyExists("vsync"))
		Ak::Core::ProjectFile::setBoolValue("vsync", true);
	
	_eltm->load(std::move(Ak::Core::ProjectFile::getStringValue("language")));

	Ak::WindowComponent::onAttach();
	Ak::WindowComponent::title = _eltm->getLocalText("window_title");
	Ak::WindowComponent::resizable = true;
	Ak::WindowComponent::maximize = true;
	Ak::WindowComponent::vsync = Ak::Core::ProjectFile::getBoolValue("vsync");
	Ak::WindowComponent::fetchSettings();

	Ak::Render_Core::get().getClearValue().color.float32[0] = 0.627450980;
	Ak::Render_Core::get().getClearValue().color.float32[1] = 0.878431373;
	Ak::Render_Core::get().getClearValue().color.float32[2] = 0.909803922;

	_stack = Ak::create_Unique_ptr<PanelStack>();

	_stack->add_panel<Docks>(_eltm);
	_stack->add_panel<Scene>(_eltm);
	_stack->add_panel<ELTM_editor>(_eltm, &_eltm_editor_input_buffer, &_eltm_editor_save);
	_stack->add_panel<Entities>(_eltm);
	_stack->add_panel<EntitiesManager>(_eltm);
	_stack->add_panel<RendererManager>(_eltm);
	_stack->add_panel<AudioManager>(_eltm);
	_stack->add_panel<Materials>(_eltm);
	_stack->add_panel<MaterialEditor>(_eltm);
	_stack->add_panel<Browser>(_eltm);
	_stack->add_panel<Console>(_eltm);
}

void StudioComponent::setContext()
{
    ImGuizmo::SetImGuiContext(ImGui::GetCurrentContext());
}

static bool realquit = false;

void StudioComponent::onImGuiRender()
{
	ImGuizmo::BeginFrame();

	drawMainMenuBar();

	for(auto elem : _stack->_panels)
		elem->onUpdate(size);

	if(_showAbout)
		drawAboutWindow();
	if(_showOpt)
		drawOptionsWindow();

	if(!realquit && !_running)
        ImGui::OpenPopup(_eltm->getLocalText("really").c_str());

	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if(ImGui::BeginPopupModal(_eltm->getLocalText("really").c_str(), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		ImGui::Text(_eltm->getLocalText("are_you_sure_quit").c_str());
		if(ImGui::Button(_eltm->getLocalText("yes").c_str(), ImVec2(120, 0)))
		{
			_running = false;
			realquit = true;
			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();

		if(ImGui::Button(_eltm->getLocalText("no").c_str(), ImVec2(120, 0)))
		{
			_running = true;
			realquit = false;
			ImGui::CloseCurrentPopup();
		}
		
		ImGui::EndPopup();
	}
}

void StudioComponent::onImGuiEvent(Ak::Input& input)
{
	_running = _running == true ? !input.isEnded() : _running;
	if(!_running && !Ak::Core::ProjectFile::getBoolValue("on_quit_window"))
		realquit = true;
	if(realquit)
		input.finish();

	if(input.isEnded() && !realquit)
		input.run();

	for(auto elem : _stack->_panels)
		elem->onEvent(input);
	
	_eltm_editor_input_buffer.clear();

	Ak::WindowComponent::onEvent(input);
}

void StudioComponent::onQuit()
{
	for(auto elem : _stack->_panels)
		elem->onQuit();
	_stack.reset(nullptr);
	_lang_eltm.reset(nullptr);
	Ak::WindowComponent::onQuit();
}

void StudioComponent::drawMainMenuBar()
{
	if(ImGui::BeginMainMenuBar())
	{
		if(ImGui::BeginMenu(_eltm->getLocalText("MainMenuBar.file").c_str()))
		{
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.open").c_str(), "Ctrl+O"))
				auto file = pfd::open_file(_eltm->getLocalText("MainMenuBar.open"), Ak::Core::getMainDirPath(), { "Akel projects (.akel)", "*.akel" });	
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
				_showOpt = !_showOpt;
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
				_eltm_editor_save = 1;
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.e_save_as").c_str()))
				_eltm_editor_save = 2;
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu(_eltm->getLocalText("MainMenuBar.help").c_str()))
		{
			if(ImGui::MenuItem(_eltm->getLocalText("MainMenuBar.about").c_str()))
				_showAbout = _showAbout ? false : true;
			ImGui::EndMenu();
		}
		ImGui::SameLine(size.X - 100);
		ImGui::Text("%d FPS", Ak::CounterFPS::getFPS());

		ImGui::EndMainMenuBar();
	}
}

void StudioComponent::drawAboutWindow()
{
	if(ImGui::Begin(_eltm->getLocalText("MainMenuBar.about").data(), &_showAbout, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
	{
		ImGui::TextUnformatted(_eltm->getLocalText("MainMenuBar.version").data());
		ImGui::End();
	}
}

extern bool reload_docks;

void StudioComponent::draw_general_settings()
{
	ImGui::Text(_eltm->getLocalText("Settings.language").data());
	ImGui::SameLine();
	static std::string selected = _eltm->getLocalText("lang_name");
	if(ImGui::BeginCombo("##combo", selected.c_str()))
	{
		for(auto&& [lang, path] : _lang_eltm->getCurrentTexts())
		{
			if(ImGui::Selectable(lang.c_str(), selected == lang))
			{
				_eltm->reload(Ak::Core::getMainDirPath() + path);
				Ak::Core::ProjectFile::setStringValue("language", Ak::Core::getMainDirPath() + path);
				selected = lang;
				reload_docks = true;
			}
		}

		ImGui::EndCombo();
	}

	ImGui::Separator();

	bool on_quit_window = Ak::Core::ProjectFile::getBoolValue("on_quit_window");
	ImGui::Checkbox(_eltm->getLocalText("Settings.onQuit").c_str(), &on_quit_window);
	if(on_quit_window != Ak::Core::ProjectFile::getBoolValue("on_quit_window"))
		Ak::Core::ProjectFile::setBoolValue("on_quit_window", on_quit_window);
}

void StudioComponent::drawOptionsWindow()
{
	if(ImGui::Begin(_eltm->getLocalText("MainMenuBar.options").data(), &_showOpt, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		static int selected = -1;
		
    	if(ImGui::BeginChild("Panel", ImVec2(200, 0), true))
		{
			if(ImGui::Selectable(_eltm->getLocalText("Settings.general").data(), selected == 0))
				selected = 0;
			ImGui::EndChild();
		}

		ImGui::SameLine(0);

		if(ImGui::BeginChild("Choices", ImVec2(0, 0), true))
		{
			switch(selected)
			{
				case 0: draw_general_settings(); break;

				default : break;
			}

			ImGui::EndChild();
		}

		ImGui::End();
	}	
}
