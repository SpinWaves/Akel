// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 22/02/2023
// Updated : 02/05/2023

#include "launcher_component.h"

static bool quit = false;

void LauncherComponent::onAttach()
{
	_logo = AkImGui::LoadImage(Ak::Core::getMainDirPath() + "resources/assets/logo.png");

	ImGuiIO& io = ImGui::GetIO();
	_tiny_font = io.Fonts->AddFontFromFileTTF(std::string(Ak::Core::getMainDirPath() + "resources/fonts/opensans/OpenSans-Regular.ttf").c_str(), 15.0f);
	_title_font = io.Fonts->AddFontFromFileTTF(std::string(Ak::Core::getMainDirPath() + "resources/fonts/opensans/OpenSans-Regular.ttf").c_str(), 45.0f);
}

void LauncherComponent::onImGuiRender()
{
	static Ak::WindowComponent* window = Ak::getMainAppComponentStack()->get_component_as<Ak::WindowComponent>("__window_component");
	if(ImGui::Begin("main", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking))
	{
		ImGui::SetWindowPos(ImVec2(0, 0));
		ImGui::SetWindowSize(ImVec2(window->size.X, window->size.Y));

		ImGui::Image(_logo.getImGuiID(), ImVec2(50, 50));
		ImGui::SameLine();
		ImGui::PushFont(_title_font);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
		ImGui::Text("Akel Studio");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		
		drawMainContent();
		ImGui::SameLine();
		drawSideBar();

		ImGui::End();
	}
}

void LauncherComponent::onImGuiEvent(Ak::Input& input)
{
	if(quit)
		input.finish();
}

void LauncherComponent::onQuit()
{
	_logo.destroy();
	for(const Project& project : _projects)
		const_cast<Project&>(project).icon.destroy();
}

void LauncherComponent::drawMainContent()
{
	constexpr ImVec2 child_size = ImVec2(585, 65);
	if(ImGui::BeginChild("main_content", ImVec2(600, 0), true))
	{
		for(const Project& project : _projects)
		{
			if(ImGui::BeginChild(project.title.c_str(), child_size, true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
			{
				ImGui::Image(const_cast<Project&>(project).icon.getImGuiID(), ImVec2(50, 50));
				ImGui::SameLine();

				if(ImGui::BeginChild(std::string(project.title + "_intenal").c_str(), ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground))
				{
					ImGui::TextUnformatted(project.title.c_str());

					ImGui::PushFont(_tiny_font);
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
							ImGui::TextUnformatted(project.folder.parent_path().string().c_str());
						ImGui::PopStyleColor();
					ImGui::PopFont();

					ImGui::EndChild();
				}

				ImGui::EndChild();
			}
			ImGui::Separator();
		}

		ImGui::EndChild();
	}
}

void LauncherComponent::drawSideBar()
{
	if(ImGui::BeginChild("side_content", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar))
	{
		if(ImGui::Button("New Project", ImVec2(ImGui::GetWindowWidth() - 18, 0)))
		{
			if(!_new_project_window)
			{
				if(_currently_creating.has_value())
					_currently_creating.reset();
				_error_no_name = false;
				_error_no_name = false;
				_warn_not_empty = false;
				_currently_creating.emplace(AkImGui::LoadImage(Ak::Core::getMainDirPath() + "resources/assets/logo_icon.png"), "", "");
			}
			_new_project_window = true;
		}
		if(ImGui::Button("Import Project", ImVec2(ImGui::GetWindowWidth() - 18, 0)))
		{
			auto file = pfd::open_file("Import Project", "", { "Akel projects (.akel)", "*.akel" }).result();
			if(!file.empty())
			{
				std::filesystem::path path = file[0];
				_projects.emplace(AkImGui::LoadImage(Ak::Core::getMainDirPath() + "resources/assets/logo_icon.png"), path.stem().string(), path);
			}
		}
		ImGui::Separator();
		if(ImGui::Button("Quit", ImVec2(ImGui::GetWindowWidth() - 18, 0)))
			quit = true;

		ImGui::Dummy(ImVec2(10, ImGui::GetWindowHeight() - ImGui::GetCursorPosY() - ImGui::GetTextLineHeightWithSpacing() * 2));
		ImGui::Separator();

		ImGui::PushFont(_tiny_font);
			ImGui::Text("Akel Version 0.0.1");
			ImGui::Text("Akel Studio Version 0.0.1");
		ImGui::PopFont();

		ImGui::EndChild();
	}

	if(_new_project_window)
	{
		static Ak::WindowComponent* window = Ak::getMainAppComponentStack()->get_component_as<Ak::WindowComponent>("__window_component");
		ImGui::SetNextWindowPos(ImVec2(window->size.X / 2.0f - 200.0f, window->size.Y / 2.0f - 150.0f), ImGuiCond_Appearing);
		ImGui::SetNextWindowSize(ImVec2(400.0f, 300.0f));
		ImGui::SetNextWindowFocus();
		if(ImGui::Begin("New Project", &_new_project_window, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
		{
			if(ImGui::BeginChild("##new_project_child", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
			{
				ImGui::TextUnformatted("Project's Name :");
				if(_error_no_name)
				{
					ImGui::SameLine();
					ImGui::PushFont(_tiny_font);
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.365f, 0.365f, 1.0f));
							ImGui::TextUnformatted("Your project needs a name !");
						ImGui::PopStyleColor();
					ImGui::PopFont();
				}
				if(AkImGui::InputText("##project_name", &_currently_creating->title, ImGuiInputTextFlags_AutoSelectAll))
					_error_no_name = false;

				ImGui::TextUnformatted("Project's Folder :");
				if(!_currently_creating->folder.empty())
					_error_no_path = false;
				if(_error_no_path)
				{
					ImGui::SameLine();
					ImGui::PushFont(_tiny_font);
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.365f, 0.365f, 1.0f));
							ImGui::TextUnformatted("Your project needs a folder !");
						ImGui::PopStyleColor();
					ImGui::PopFont();
				}
				else if(!_currently_creating->folder.empty() && !std::filesystem::is_empty(_currently_creating->folder))
				{
					ImGui::SameLine();
					ImGui::PushFont(_tiny_font);
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 0.f, 1.f));
							ImGui::TextUnformatted("This file is not empty, be warn");
						ImGui::PopStyleColor();
					ImGui::PopFont();
				}

				if(!_currently_creating->folder.empty())
				{
					ImGui::PushFont(_tiny_font);
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
							ImGui::TextUnformatted(_currently_creating->folder.string().c_str());
						ImGui::PopStyleColor();
					ImGui::PopFont();
				}
				if(ImGui::Button("Select Folder"))
				{
					auto dialog = pfd::select_folder("Select project folder", "", pfd::opt::force_path);
					_currently_creating->folder = dialog.result();
				}

				ImGui::SetCursorPosY(ImGui::GetWindowHeight() - (ImGui::GetFontSize() * 2.0f) - 10);

				if(ImGui::Button(AKS_ICON_MD_NOTE_ADD " Create Project And Setup Folder", ImVec2(ImGui::GetWindowWidth() - 15.0f, ImGui::GetFontSize() * 2.0f)))
				{
					if(_currently_creating->title.empty())
						_error_no_name = true;
					else if(_currently_creating->folder.empty())
						_error_no_path = true;
					else
					{
						_projects.insert(*_currently_creating);
						_new_project_window = false;
					}
				}
				ImGui::EndChild();
			}
			ImGui::End();
		}
	}
}

void LauncherComponent::generateFontTextures(Ak::ImGuiComponent* imgui)
{
	ImGuiIO& io = ImGui::GetIO();
	imgui->addFontFromFile(std::string(Ak::Core::getMainDirPath() + "resources/fonts/opensans/OpenSans-Regular.ttf").c_str(), 20.0f, true);
	static const ImWchar icons_ranges[] = { AKS_ICON_MIN_MD, AKS_ICON_MAX_16_MD, 0 };
	ImFontConfig config;
	config.MergeMode = true;
	config.GlyphOffset.y = 4.0f;

	io.Fonts->AddFontFromFileTTF(std::string(Ak::Core::getMainDirPath() + "resources/fonts/material_icons-regular.ttf").c_str(), 20.0f, &config, icons_ranges);
	io.Fonts->AddFontDefault();
	imgui->generateFonts();
}
