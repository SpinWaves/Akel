#include <Akel.h>
#include <Akel_main.h>

Ak::AkelInstance Akel_init()
{
	Ak::AkelInstance project;
		project.project_file_path = Ak::Core::getMainDirPath();
		project.project_file_name = "app";
	return project;
}

Ak::Application* Akel_mainApp()
{
	Ak::Application* app = Ak::memAlloc<Ak::Application>();
	app->add_component<Ak::lua::LuaComponent>();
	return app;
}
