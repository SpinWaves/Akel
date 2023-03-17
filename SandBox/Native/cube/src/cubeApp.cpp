#include <Akel.h>
#include <Akel_main.h>

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
        instance.project_file_path = Ak::Core::getMainDirPath();
        instance.project_file_name = "cube";
    return instance;
}

Ak::Application* Akel_mainApp(Ak::CommandLineArgs args)
{
	Ak::PlainApplication* app = Ak::memAlloc<Ak::PlainApplication>("Cube using Akel Engine");
	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene");
	scene->addCamera<Ak::Cam::FirstPerson3D>(-5.0f, 1.0f, 0.0f);
	app->add_scene(scene);

	Ak::MaterialDesc material_desc;
	material_desc.albedo = Ak::Res::get().getTexturesPath() / "rodriguez.jpg";
	Ak::MaterialID material = Ak::addMaterialToLibrary(material_desc);

	Ak::Entity cube = scene->createEntity();
	cube.addAttribute<Ak::TransformAttribute>(1.0f, 1.0f, 1.0f);
	cube.addAttribute<Ak::ModelAttribute>(Ak::createCube(), material);
	
	return app;
}
