// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 09/09/2023

#include <AkSpch.h>
#include <Akel_main.h>
#include <studioComponent.h>
#include <Fonts/material_font.h>

void Akel_InstanceSetup(Ak::AkelInstance& project)
{
	project.project_file_path = Ak::VFS::getMainDirPath() / "settings";
	project.project_file_name = "akel_studio";
	project.use_default_resource_system = false;
}

void Akel_AppSetup(Ak::Application& app, Ak::CommandLineArgs args)
{
	if(args.count != 2)
		Ak::FatalError("Akel Studio : wrong args number");

	Ak::Core::printEngineHeader(); // just for style

	app.add_component<Ak::AudioComponent>();

	Ak::WindowComponent* window = app.add_component<Ak::WindowComponent>();
	Ak::RendererComponent* renderer = app.add_component<Ak::RendererComponent>(window);
	renderer->setMaxFPS(200);
	app.add_component<Ak::SceneManager>(renderer);

	Ak::ImGuiComponent* imgui = app.add_component<Ak::ImGuiComponent>(renderer, std::filesystem::path(Ak::VFS::getMainDirPath() / "settings/akel_studio_imgui.ini").string(), false);

	StudioComponent* studio = app.add_component<StudioComponent>(args);
	studio->generateFontTextures(imgui);
}
