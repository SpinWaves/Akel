// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 22/07/2022

#include <AkSpch.h>
#include <Akel_main.h>
#include <studioComponent.h>

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
			add_component<Ak::ImGuiComponent>();
			
			studio->setContext();
		}
		~Studio() = default;
};

Ak::AkelInstance Akel_init()
{
	Ak::AkelInstance project;
		project.project_file_path = std::string(Ak::Core::getMainDirPath() + "Akel_Studio/settings");
		project.project_file_name = "akel_studio";
        project.memory_manager_enable_fixed_allocator = false;
		project.vk_force_disable_validation_layers = true; // TODO : remove that
	return project;
}

Ak::Application* Akel_mainApplication()
{
	return Ak::memAlloc<Studio>();
}
