#include <Akel.h>
#include <Akel_main.h>

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
        instance.project_file_path = Ak::Core::getMainDirPath();
        instance.project_file_name = "model";
    return instance;
}

Ak::Application* Akel_mainApp()
{
	Ak::PlainApplication* app = Ak::memAlloc<Ak::PlainApplication>("Model Loading using Akel Engine");
	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene");
	scene->addCamera<Ak::Cam::FirstPerson3D>(1.0f, 1.0f, 1.0f);
	app->add_scene(scene);

	Ak::Entity lem = scene->createEntity();
	lem.addAttribute<Ak::TransformAttribute>({ 1.0f, 1.0f, 1.0f });
	lem.addAttribute<Ak::ModelAttribute>(Ak::Res::get().getMeshesPath() / "apollo_lunar_module.obj");
	
	return app;
}
