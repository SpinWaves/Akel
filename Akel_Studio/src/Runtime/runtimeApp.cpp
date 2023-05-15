// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 15/05/2023
// Updated : 15/05/2023

#include <Akel.h>
#include <Akel_main.h>

using json = nlohmann::json;

Ak::AkelInstance Akel_init()
{
	std::filesystem::path path(Ak::Core::getMainDirPath() + "settings.akrt");
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

    Ak::AkelInstance instance;
        instance.project_file_path = settings["projectFilePath"];
        instance.project_file_name = settings["projectFileName"];
		instance.memory_manager_enable_fixed_allocator = settings["memManagerEnableFixedAllocator"];
		instance.vk_enable_message_validation_layer = settings["vkEnableMessageValidationLayers"];
		instance.use_system_dialog_boxes = settings["useSystemDialogBoxes"];
		instance.enable_warning_console_message = settings["enableWarningConsoleMessage"];
		instance.vk_force_disable_validation_layers = settings["vkForceDisableValidationLayers"];
		instance.use_default_resource_system = settings["useDefaultResourceSystem"];
    return instance;
}

Ak::Application* Akel_mainApp(Ak::CommandLineArgs args)
{
	Ak::Application* app = Ak::memAlloc<Ak::Application>();

	Ak::Core::ProjectFile& project = Ak::getMainAppProjectFile();

	if(project.keyExists("__window_component"))
	{
		Ak::WindowComponent* window = app->add_component<Ak::WindowComponent>();
		window->title = project.archive()["window_component"]["title"];
		window->icon = project.archive()["window_component"]["icon"];
		window->size.X = project.archive()["window_component"]["size"]["x"];
		window->size.Y = project.archive()["window_component"]["size"]["y"];
		window->pos.X = project.archive()["window_component"]["pos"]["x"];
		window->pos.Y = project.archive()["window_component"]["pos"]["y"];
		window->minSize.X = project.archive()["window_component"]["minSize"]["x"];
		window->minSize.Y = project.archive()["window_component"]["minSize"]["y"];
		window->maxSize.X = project.archive()["window_component"]["maxSize"]["x"];
		window->maxSize.Y = project.archive()["window_component"]["maxSize"]["y"];
		window->brightness = project.archive()["window_component"]["brightnesss"];
		window->opacity = project.archive()["window_component"]["opacity"];
		window->fullscreen = project.archive()["window_component"]["fullscreen"];
		window->border = project.archive()["window_component"]["border"];
		window->resizable = project.archive()["window_component"]["resizable"];
		window->visible = project.archive()["window_component"]["visible"];
		window->vsync = project.archive()["window_component"]["vsync"];
		window->maximize = project.archive()["window_component"]["maximize"];
		window->minimize = project.archive()["window_component"]["minimize"];
		window->fetchSettings();

		if(project.keyExists("__renderer_component"))
			Ak::RendererComponent* renderer = app->add_component<Ak::RendererComponent>(window);
	}

	return app;
}
