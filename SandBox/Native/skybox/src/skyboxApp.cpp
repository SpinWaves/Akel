#include <Akel.h>
#include <Akel_main.h>

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
        instance.project_file_path = Ak::Core::getMainDirPath();
        instance.project_file_name = "skybox";
    return instance;
}

Ak::Application* Akel_mainApp(Ak::CommandLineArgs args)
{
	Ak::PlainApplication* app = Ak::memAlloc<Ak::PlainApplication>("Skyboxing using Akel Engine");
	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene");
	scene->addCamera<Ak::Cam::FirstPerson3D>(-5.0f, 1.0f, 0.0f);
	app->add_scene(scene);

	// Setting up the skybox
	Ak::SkyboxDesc sky_desc;
	sky_desc.front = Ak::Res::get().getTexturesPath() / "sky_front.png";
	sky_desc.back = Ak::Res::get().getTexturesPath() / "sky_back.png";
	sky_desc.top = Ak::Res::get().getTexturesPath() / "sky_top.png";
	sky_desc.bottom = Ak::Res::get().getTexturesPath() / "sky_bottom.png";
	sky_desc.left = Ak::Res::get().getTexturesPath() / "sky_left.png";
	sky_desc.right = Ak::Res::get().getTexturesPath() / "sky_right.png";
	scene->addSkybox(std::move(sky_desc));

	// Setting up Spaceship model and material
	Ak::MaterialDesc spaceship_material_desc;
	spaceship_material_desc.albedo = Ak::Res::get().getTexturesPath() / "spaceship_map.jpg";
	Ak::MaterialID spaceship_material = Ak::addMaterialToLibrary(spaceship_material_desc);

	Ak::Entity spaceship = scene->createEntity();
	spaceship.addAttribute<Ak::TransformAttribute>(0.0f, 0.0f, 0.0f);
	spaceship.addAttribute<Ak::ModelAttribute>(Ak::Res::get().getMeshesPath() / "spaceship.obj", spaceship_material);

	return app;
}
