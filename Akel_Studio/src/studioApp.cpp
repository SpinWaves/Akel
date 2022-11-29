// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 29/11/2022

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
	return project;
}

Ak::Application* Akel_mainApp()
{
	Ak::Application* app = Ak::memAlloc<Ak::Application>();
	Ak::Core::printEngineInfo();
	app->add_component<Ak::AudioManager>();

	StudioComponent* studio = Ak::memAlloc<StudioComponent>();
	SceneCamera* camera = Ak::memAlloc<SceneCamera>(-5, 3, -5, &studio->size);
	studio->setCamera(camera);
	app->add_component(camera);
	app->add_component(studio);

	Ak::RendererComponent* renderer = Ak::memAlloc<Ak::RendererComponent>(static_cast<Ak::WindowComponent*>(studio));

	renderer->loadCustomShader(Ak::Core::getMainDirPath() + "ressources/shaders/2D/vert.spv");
	renderer->loadCustomShader(Ak::Core::getMainDirPath() + "ressources/shaders/2D/frag.spv");

	Ak::Entity2D rectangle(Models::quad, { -0.5f, -0.5f }, { 1.f, 1.f }, Colors::red);
	renderer->add_entity(rectangle);

	app->add_component(renderer);

	Ak::ImGuiComponent* imgui = Ak::memAlloc<Ak::ImGuiComponent>();
	imgui->setSettingsFilePath(std::string(Ak::Core::getMainDirPath() + "settings/akel_studio_imgui.ini").c_str());
	app->add_component(imgui);

	studio->setContext();
	studio->generateFontTextures(imgui);

	return app;
}
