// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 16/08/2022

#include <AkSpch.h>
#include <Akel_main.h>
#include <studioComponent.h>
#include <Fonts/material_font.h>

class Studio : public Ak::Application
{
	public:
		Studio() : Ak::Application("Akel Studio")
		{
			Ak::Core::printEngineInfo();
			add_component<Ak::AudioManager>();

			StudioComponent* studio = Ak::memAlloc<StudioComponent>();
			add_component(studio);

			add_component<Ak::RendererComponent>(static_cast<Ak::WindowComponent*>(studio));
			Ak::ImGuiComponent* imgui = Ak::memAlloc<Ak::ImGuiComponent>();
			imgui->setSettingsFilePath(std::string(Ak::Core::getMainDirPath() + "settings/akel_studio_imgui.ini").c_str());
			add_component(imgui);
			studio->setContext();

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
		~Studio() = default;
};

Ak::AkelInstance Akel_init()
{
	Ak::AkelInstance project;
		project.project_file_path = std::string(Ak::Core::getMainDirPath() + "settings");
		project.project_file_name = "akel_studio";
        project.memory_manager_enable_fixed_allocator = false;
	return project;
}

Ak::Application* Akel_mainApplication()
{
	return Ak::memAlloc<Studio>();
}
