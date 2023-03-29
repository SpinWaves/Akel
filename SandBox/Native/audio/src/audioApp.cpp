#include <Akel.h>
#include <Akel_main.h>

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
        instance.project_file_path = Ak::Core::getMainDirPath();
        instance.project_file_name = "audio";
    return instance;
}

Ak::Application* Akel_mainApp(Ak::CommandLineArgs args)
{
	Ak::PlainApplication* app = Ak::memAlloc<Ak::PlainApplication>("Audio using Akel Engine");
	app->add_component<Ak::AudioComponent>();

	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene");
	scene->addCamera<Ak::Cam::FirstPerson3D>(-5.0f, 1.0f, 0.0f);
	app->add_scene(scene);

	// Setting up Spaceship model and material
	Ak::MaterialDesc spaceship_material_desc;
	spaceship_material_desc.albedo = Ak::Res::get().getTexturesPath() / "spaceship_map.jpg";
	Ak::MaterialID spaceship_material = Ak::addMaterialToLibrary(spaceship_material_desc);

	Ak::Entity spaceship = scene->createEntity();
	spaceship.addAttribute<Ak::TransformAttribute>(0.0f, 0.0f, 0.0f);
	spaceship.addAttribute<Ak::AudioAttribute>(Ak::Res::get().getSoundsPath() / "engine.ogg");
	spaceship.addAttribute<Ak::ModelAttribute>(Ak::Res::get().getMeshesPath() / "spaceship.obj", spaceship_material);

	Ak::LuaLoader lua(app, *app->getSceneManager());
	spaceship.addAttribute<Ak::ScriptAttribute>(lua.loadScript(Ak::Res::get().getScriptsPath() / "spaceship_script.lua"));

	return app;
}
