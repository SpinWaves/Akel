// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 06/07/2021
// Updated : 28/08/2022

#include <studioComponent.h>
#include <Fonts/material_font.h>

Ak::Unique_ptr<Ak::ELTM> _lang_eltm(nullptr);

StudioComponent::StudioComponent() : Ak::WindowComponent(), _eltm(Ak::create_shared_ptr_w<Ak::ELTM>()) {}

void StudioComponent::onAttach()
{
	_lang_eltm = Ak::create_Unique_ptr<Ak::ELTM>();
	_lang_eltm->load(Ak::Core::getMainDirPath() + "texts/langs.eltm");

	if(!Ak::Core::ProjectFile::keyExists("language"))
		Ak::Core::ProjectFile::setStringValue("language", Ak::Core::getMainDirPath() + _lang_eltm->getText("English"));
	if(!Ak::Core::ProjectFile::keyExists("on_quit_window"))
		Ak::Core::ProjectFile::setBoolValue("on_quit_window", true);
	if(!Ak::Core::ProjectFile::keyExists("vsync"))
		Ak::Core::ProjectFile::setBoolValue("vsync", true);
	
	_eltm->load(std::move(Ak::Core::ProjectFile::getStringValue("language")));

	Ak::WindowComponent::onAttach();
	Ak::WindowComponent::title = std::move(_eltm->getText("window_title"));
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
	ImGuizmo::Enable(true);

	drawMainMenuBar();

	for(auto elem : _stack->_panels)
		elem->onUpdate(size);

	if(_showAbout)
		drawAboutWindow();
	if(_showOpt)
		drawOptionsWindow();

	if(!realquit && !_running)
        ImGui::OpenPopup(_eltm->getText("really").c_str());

	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if(ImGui::BeginPopupModal(_eltm->getText("really").c_str(), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		ImGui::Text(_eltm->getText("are_you_sure_quit").c_str());
		if(ImGui::Button(_eltm->getText("yes").c_str(), ImVec2(120, 0)))
		{
			_running = false;
			realquit = true;
			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();

		if(ImGui::Button(_eltm->getText("no").c_str(), ImVec2(120, 0)))
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
}

void StudioComponent::generateFontTextures(Ak::ImGuiComponent* imgui)
{
	ImGuiIO& io = ImGui::GetIO();
	imgui->addFontFromFile(std::string(Ak::Core::getMainDirPath() + "fonts/opensans/OpenSans-Regular.ttf").c_str(), 19.0f, true);
	static const ImWchar icons_ranges[] = { AKS_ICON_MIN_MD, AKS_ICON_MAX_16_MD, 0 };
	ImFontConfig config;
	config.MergeMode = true;
	config.GlyphOffset.y = 4.0f;

	io.Fonts->AddFontFromFileTTF(std::string(Ak::Core::getMainDirPath() + "fonts/material_icons-regular.ttf").c_str(), 19.0f, &config, icons_ranges);
	io.Fonts->AddFontDefault();
	imgui->generateFonts();
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
		if(ImGui::BeginMenu(std::string(AKS_ICON_MD_FOLDER" " + _eltm->getText("MainMenuBar.file")).c_str()))
		{
			if(ImGui::MenuItem(std::string(AKS_ICON_MD_FILE_OPEN" " + _eltm->getText("MainMenuBar.open")).c_str(), "Ctrl+O"))
				auto file = pfd::open_file(_eltm->getText("MainMenuBar.open"), Ak::Core::getMainDirPath(), { "Akel projects (.akel)", "*.akel" });	
			if(ImGui::MenuItem(std::string(AKS_ICON_MD_SAVE" " + _eltm->getText("MainMenuBar.save")).c_str(), "Ctrl+S")) { /* Do stuff */ }
			if(ImGui::MenuItem(std::string(AKS_ICON_MD_CLOSE" " + _eltm->getText("MainMenuBar.quit")).c_str()))
				_running = false;
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu(std::string(AKS_ICON_MD_TUNE" " + _eltm->getText("MainMenuBar.edit")).c_str()))
		{
			if(ImGui::MenuItem(std::string(AKS_ICON_MD_NOTE_ADD" " + _eltm->getText("MainMenuBar.addFile")).c_str())) { /* Do stuff */ }
			if(ImGui::MenuItem(std::string(AKS_ICON_MD_BUILD_CIRCLE" " + _eltm->getText("MainMenuBar.build")).c_str()))   { /* Do stuff */ }
			if(ImGui::MenuItem(std::string(AKS_ICON_MD_SETTINGS" " + _eltm->getText("MainMenuBar.options")).c_str()))
				_showOpt = !_showOpt;
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu(std::string(AKS_ICON_MD_GRID_VIEW" " + _eltm->getText("MainMenuBar.panels")).c_str()))
		{
			if(ImGui::MenuItem(std::string(AKS_ICON_MD_TYPE_SPECIMEN" " + _eltm->getText("ELTM_Editor.name")).c_str()))
				_stack->get_panel("__eltm_editor")->onOpen();
			ImGui::EndMenu();
		}
		if(_stack->get_panel("__eltm_editor")->isOpen() && ImGui::BeginMenu(std::string(AKS_ICON_MD_TYPE_SPECIMEN" " + _eltm->getText("MainMenuBar.eltm_editor")).c_str()))
		{
			if(ImGui::MenuItem(std::string(AKS_ICON_MD_FILE_OPEN" " + _eltm->getText("MainMenuBar.e_load")).c_str()))
			{
				auto file = pfd::open_file(_eltm->getText("MainMenuBar.e_load"), Ak::Core::getMainDirPath(), { "ELTM files (.eltm .tm)", "*.eltm *.tm", "All files", "*"});	
				if(!file.result().empty())
					_eltm_editor_input_buffer = file.result()[0];
			}
			if(ImGui::MenuItem(std::string(AKS_ICON_MD_SAVE" " + _eltm->getText("MainMenuBar.e_save")).c_str()))
				_eltm_editor_save = 1;
			if(ImGui::MenuItem(std::string(AKS_ICON_MD_SAVE_AS" " + _eltm->getText("MainMenuBar.e_save_as")).c_str()))
				_eltm_editor_save = 2;
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu(std::string(AKS_ICON_MD_HELP" " + _eltm->getText("MainMenuBar.help")).c_str()))
		{
			if(ImGui::MenuItem(std::string(AKS_ICON_MD_INFO" " + _eltm->getText("MainMenuBar.about")).c_str()))
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
	if(ImGui::Begin(std::string(AKS_ICON_MD_INFO" " + _eltm->getText("MainMenuBar.about")).data(), &_showAbout, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
	{
		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - ImGui::CalcTextSize(_eltm->getText("MainMenuBar.version").data()).x - 30, ImGui::GetWindowHeight() - ImGui::GetTextLineHeightWithSpacing() * 2.5));
		ImGui::TextUnformatted(_eltm->getText("MainMenuBar.version").data());

#ifdef AK_STUDIO_DEBUG
		ImGui::TextUnformatted("Debug version");
#else
		ImGui::TextUnformatted("Release version");
#endif
		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 1.75f, size.Y - (size.Y / 1.2f)));
		ImGui::TextWrapped(_eltm->getText("MainMenuBar.about_text").data());

		AkImGui::WebLink(_eltm->getText("MainMenuBar.license").data(), "https://akel-engine.com/license/", ImVec2(ImGui::GetWindowWidth()/2 - ImGui::CalcTextSize(_eltm->getText("MainMenuBar.website").data()).x * 2 - ImGui::CalcTextSize(_eltm->getText("MainMenuBar.license").data()).x, ImGui::GetWindowHeight() - ImGui::GetWindowHeight()/4));
		AkImGui::WebLink(_eltm->getText("MainMenuBar.website").data(), "https://akel-engine.com/", ImVec2(ImGui::GetWindowWidth()/2 - ImGui::CalcTextSize(_eltm->getText("MainMenuBar.website").data()).x/2, ImGui::GetWindowHeight() - ImGui::GetWindowHeight()/4));
		AkImGui::WebLink(_eltm->getText("MainMenuBar.code").data(), "https://github.com/Spinwaves/Akel", ImVec2(ImGui::GetWindowWidth()/2 + ImGui::CalcTextSize(_eltm->getText("MainMenuBar.website").data()).x * 2, ImGui::GetWindowHeight() - ImGui::GetWindowHeight()/4));

		ImGui::End();
	}
}

extern bool reload_docks;

void StudioComponent::draw_general_settings()
{
	ImGui::Text(std::string(AKS_ICON_MD_LANGUAGE" " + _eltm->getText("Settings.language")).data());
	ImGui::SameLine();
	static std::string selected = _eltm->getText("lang_name");
	if(ImGui::BeginCombo("##combo", selected.c_str()))
	{
		for(auto&& [lang, path] : _lang_eltm->getTexts())
		{
			if(ImGui::Selectable(lang.c_str(), selected == lang))
			{
				if(!_eltm->reload(Ak::Core::getMainDirPath() + path))
					Ak::Core::log::report(FATAL_ERROR, "unable to change language");
				Ak::Core::ProjectFile::setStringValue("language", Ak::Core::getMainDirPath() + path);
				selected = lang;
				reload_docks = true;
			}
		}

		ImGui::EndCombo();
	}

	ImGui::Separator();

	bool on_quit_window = Ak::Core::ProjectFile::getBoolValue("on_quit_window");
	ImGui::Checkbox(_eltm->getText("Settings.onQuit").c_str(), &on_quit_window);
	if(on_quit_window != Ak::Core::ProjectFile::getBoolValue("on_quit_window"))
		Ak::Core::ProjectFile::setBoolValue("on_quit_window", on_quit_window);
}

void StudioComponent::drawOptionsWindow()
{
	if(ImGui::Begin(std::string(AKS_ICON_MD_SETTINGS" " + _eltm->getText("MainMenuBar.options")).data(), &_showOpt, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		static int selected = -1;
		
    	if(ImGui::BeginChild("Panel", ImVec2(200, 0), true))
		{
			if(ImGui::Selectable(std::string(AKS_ICON_MD_TUNE" " + _eltm->getText("Settings.general")).data(), selected == 0))
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
