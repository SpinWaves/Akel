// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 23/08/2023

#include <Akel.h>
#include <Akel_main.h>
#include "launcher_component.h"

Ak::AkelInstance Akel_init()
{
	Ak::AkelInstance project;
		project.project_file_path = Ak::VFS::getMainDirPath() / "settings";
		project.project_file_name = "akel_studio_launcher";
		project.use_default_resource_system = false;
		project.at_akel_exit = launchAkelStudio;
	return project;
}

Ak::Application* Akel_mainApp(Ak::CommandLineArgs args)
{
	Ak::Application* app = Ak::memAlloc<Ak::Application>();
	Ak::WindowComponent* window = app->add_component<Ak::WindowComponent>();
	window->title = "Akel Studio Launcher";
	window->size = { 800, 400 };
	window->pos = { AK_WINDOW_POS_CENTER, AK_WINDOW_POS_CENTER };
	window->border = false;
	window->resizable = false;
	window->vsync = true;
	window->fetchSettings();

	Ak::CounterTicks::setTicksGoal(30);

	Ak::RendererComponent* renderer = app->add_component<Ak::RendererComponent>(window);
	renderer->setMaxFPS(30);

	Ak::ImGuiComponent* imgui = app->add_component<Ak::ImGuiComponent>(renderer, std::filesystem::path(Ak::VFS::getMainDirPath() / "settings/akel_studio_launcher_imgui.ini").string(), false);

	LauncherComponent* launcher = app->add_component<LauncherComponent>();
	launcher->generateFontTextures(imgui);

	return app;
}
