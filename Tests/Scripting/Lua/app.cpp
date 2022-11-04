#include <Akel.h>
#include <Akel_main.h>

Ak::AkelInstance Akel_init()
{
	Ak::Application* app = Ak::memAlloc<Ak::Application>();
	app->add_component<Ak::lua::LuaComponent>();

	Ak::AkelInstance project;
		project.project_file_path = Ak::Core::getMainDirPath();
		project.project_file_name = "app";
        project.memory_manager_enable_fixed_allocator = false;
		project.app = app;
	return project;
}
