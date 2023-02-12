#include <Akel.h>
#include <Akel_main.h>

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
        instance.project_file_path = Ak::Core::getMainDirPath();
        instance.project_file_name = "cube";
    return instance;
}

Ak::Application* Akel_mainApp()
{
	Ak::PlainApplication* app = Ak::memAlloc<Ak::PlainApplication>("Cube using Akel Engine");
	app->add_component<Ak::Camera3D>(0, 2, 0);
	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene");
	app->add_scene(scene);

	Ak::Entity cube = scene->createEntity();
	cube.addAttribute<Ak::TextureAttribute>(Ak::Res::get().getTexturesPath() / "rodriguez.png");
	cube.addAttribute<Ak::TransformAttribute>({ 1.0f, 1.0f, 1.0f });
	
	return app;
}
