// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 22/02/2023
// Updated : 01/05/2023

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
	static auto window = static_cast<Ak::WindowComponent*>(Ak::getMainAppComponentStack()->get_component("__window_component"));
	if(ImGui::Begin("main", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove))
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
}

void LauncherComponent::drawMainContent()
{
	constexpr ImVec2 child_size = ImVec2(585, 50);
	if(ImGui::BeginChild("main_content", ImVec2(600, 0), true))
	{
		for(auto& project : _projects)
		{
			if(ImGui::BeginChild(project.title.c_str(), child_size, true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
			{
				ImGui::Text(project.title.c_str());
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

		}
		if(ImGui::Button("Import Project", ImVec2(ImGui::GetWindowWidth() - 18, 0)))
		{
			auto file = pfd::open_file("Import Project", "", { "Akel projects (.akel)", "*.akel" }).result();
			if(!file.empty())
			{
				std::filesystem::path title = file[0];
				_projects.emplace(AkImGui::ImImage{}, title.stem().string(), "");
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
