#include <Akel.h>
#include <Akel_main.h>

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
        instance.project_file_path = Ak::Core::getMainDirPath();
        instance.project_file_name = "sponza";
    return instance;
}

Ak::Application* Akel_mainApp(Ak::CommandLineArgs args)
{
	Ak::PlainApplication* app = Ak::memAlloc<Ak::PlainApplication>("Sponza using Akel Engine");

	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene");
	scene->addCamera<Ak::Cam::FirstPerson3D>(-5.0f, 1.0f, 0.0f);
	app->add_scene(scene);

	Ak::Entity sponza = scene->createEntity();
	sponza.addAttribute<Ak::TransformAttribute>(0.0f, 0.0f, 0.0f);
	sponza.addAttribute<Ak::ModelAttribute>(Ak::Res::get().getMeshesPath() / "sponza.obj", Ak::nullmaterial);
	sponza.getAttribute<Ak::TransformAttribute>().scale = Ak::Maths::Vec3f(0.02f, 0.02f, 0.02f);

	return app;
}
