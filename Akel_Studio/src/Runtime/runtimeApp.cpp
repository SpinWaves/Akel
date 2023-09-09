// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 15/05/2023
// Updated : 09/09/2023

#include <Akel.h>
#include <Akel_main.h>

using json = nlohmann::json;

void Akel_InstanceSetup(Ak::AkelInstance& instance)
{
	std::filesystem::path path(Ak::VFS::getMainDirPath() / "settings.akrt");
	if(!std::filesystem::exists(path))
		Ak::FatalError("Akel Runtime : no runtime settings found (there should be a 'settings.akrt' file in your executable directory)");

	std::ifstream file(std::move(path), std::ios::binary);
	if(!file.is_open())
		Ak::FatalError("Akel Runtime : unable to open the runtime settings file");

	file.unsetf(std::ios::skipws);

	file.seekg(0, std::ios::end);
		std::size_t fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<uint8_t> data;
		data.reserve(fileSize);
		data.insert(data.begin(), std::istream_iterator<uint8_t>(file), std::istream_iterator<uint8_t>());
	file.close();

	json settings = json::from_msgpack(std::move(data));

	instance.project_file_path = Ak::VFS::resolve(settings["projectFilePath"]);
	instance.project_file_name = settings["projectFileName"];
	instance.memory_manager_enable_fixed_allocator = settings["memManagerEnableFixedAllocator"];
	instance.vk_enable_message_validation_layer = settings["vkEnableMessageValidationLayers"];
	instance.use_system_dialog_boxes = settings["useSystemDialogBoxes"];
	instance.enable_warning_console_message = settings["enableWarningConsoleMessage"];
	instance.vk_force_disable_validation_layers = settings["vkForceDisableValidationLayers"];
	instance.use_default_resource_system = settings["useDefaultResourceSystem"];
}

void Akel_AppSetup(Ak::Application& app, Ak::CommandLineArgs args)
{
	Ak::Core::ProjectFile& project = Ak::getMainAppProjectFile();

	if(project.keyExists("__window_component") && project.archive()["__window_component"] == true)
	{
		Ak::WindowComponent* window = app.add_component<Ak::WindowComponent>();
		if(project.keyExists("__renderer_component") && project.archive()["__renderer_component"] == true)
		{
			Ak::RendererComponent* renderer = app.add_component<Ak::RendererComponent>(window);
			if(project.keyExists("__imgui_component") && project.archive()["__imgui_component"] == true)
				app.add_component<Ak::ImGuiComponent>(renderer);
			if(project.keyExists("__scenes_manager_component") && project.archive()["__scenes_manager_component"] == true)
			{
				Ak::SceneManager* manager = app.add_component<Ak::SceneManager>(renderer);
				if(project.keyExists("scenes"))
				{
					for(const auto& object : project.archive()["scenes"])
					{
						std::string name = object["name"];
						Ak::Scene* scene = Ak::memAlloc<Ak::Scene>(name);
						manager->add_scene(scene);
						Ak::SceneSerializer serializer(scene);
						serializer.deserialize(Ak::VFS::resolve(object["file"]));
					}
				}
			}
		}
	}
	if(project.keyExists("__audio_component") && project.archive()["__audio_component"] == true)
		app.add_component<Ak::AudioComponent>();
	if(project.keyExists("__animator_component") && project.archive()["__animator_component"] == true)
		app.add_component<Ak::AnimatorComponent>();
}
