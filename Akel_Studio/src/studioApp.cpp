// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 16/01/2023

#include <AkSpch.h>
#include <Akel_main.h>
#include <studioComponent.h>
#include <camera.h>
#include <Fonts/material_font.h>

Ak::AkelInstance Akel_init()
{
	Ak::AkelInstance project;
		project.project_file_path = std::string(Ak::Core::getMainDirPath() + "settings");
		project.project_file_name = "akel_studio";
		project.use_default_resource_system = false;
	return project;
}

Ak::Application* Akel_mainApp()
{
	Ak::Application* app = Ak::memAlloc<Ak::Application>();
	Ak::Core::printEngineInfo();
	app->add_component<Ak::AudioComponent>();

	StudioComponent* studio = Ak::memAlloc<StudioComponent>();
	SceneCamera* camera = app->add_component<SceneCamera>(-5, 3, -5, studio);
	studio->setCamera(camera);
	app->add_component(studio);

	Ak::RendererComponent* renderer = app->add_component<Ak::RendererComponent>(static_cast<Ak::WindowComponent*>(studio));

	Ak::ImGuiComponent* imgui = Ak::memAlloc<Ak::ImGuiComponent>(renderer);
	imgui->setSettingsFilePath(std::string(Ak::Core::getMainDirPath() + "settings/akel_studio_imgui.ini").c_str());
	app->add_component(imgui);

	studio->setContext();
	studio->generateFontTextures(imgui);

	return app;
}
