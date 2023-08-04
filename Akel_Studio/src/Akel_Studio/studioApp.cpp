// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 29/07/2023

#include <AkSpch.h>
#include <Akel_main.h>
#include <studioComponent.h>
#include <Fonts/material_font.h>

Ak::AkelInstance Akel_init()
{
	Ak::AkelInstance project;
		project.project_file_path = Ak::VFS::getMainDirPath() / "settings";
		project.project_file_name = "akel_studio";
		project.use_default_resource_system = false;
	return project;
}

Ak::Application* Akel_mainApp(Ak::CommandLineArgs args)
{
	if(args.count != 2)
		Ak::FatalError("Akel Studio : wrong args number");

	Ak::Application* app = Ak::memAlloc<Ak::Application>();
	Ak::Core::printEngineHeader();

	app->add_component<Ak::AudioComponent>();

	Ak::WindowComponent* window = app->add_component<Ak::WindowComponent>();
	Ak::RendererComponent* renderer = app->add_component<Ak::RendererComponent>(window);
	renderer->setMaxFPS(200);

	Ak::ImGuiComponent* imgui = app->add_component<Ak::ImGuiComponent>(renderer, std::filesystem::path(Ak::VFS::getMainDirPath() / "settings/akel_studio_imgui.ini").string(), false);

	StudioComponent* studio = app->add_component<StudioComponent>(args);
	studio->generateFontTextures(imgui);

	return app;
}
