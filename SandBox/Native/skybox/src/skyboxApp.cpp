#include <Akel.h>
#include <Akel_main.h>

void Akel_InstanceSetup(Ak::AkelInstance& instance)
{
	instance.project_file_name = "skybox";
}

void Akel_AppSetup(Ak::Application& app, Ak::CommandLineArgs args)
{
	Ak::PlainApplication papp(app, "Skybox using Akel Engine");
	papp.add_component<Ak::ImGuiRenderStats>(papp.getRenderer());

	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene");
	scene->addCamera<Ak::Cam::FirstPerson3D>(-5.0f, 1.0f, 0.0f);
	papp.add_scene(scene);

	// Setting up the skybox
	Ak::Skybox skybox(Ak::VFS::resolve("//Textures/sky.png"));
	scene->setSkybox(skybox);

	// Setting up Spaceship model and material
	Ak::MaterialDesc spaceship_material_desc;
	spaceship_material_desc.albedo = Ak::VFS::resolve("//Textures/spaceship_map.jpg");
	Ak::MaterialID spaceship_material = Ak::addMaterialToLibrary(spaceship_material_desc);

	Ak::Entity spaceship = scene->createEntity();
	spaceship.addAttribute<Ak::TransformAttribute>(0.0f, 0.0f, 0.0f);
	spaceship.addAttribute<Ak::ModelAttribute>(Ak::VFS::resolve("//Meshes/spaceship.obj"), spaceship_material);

	Ak::Entity cube = scene->createEntity();
	cube.addAttribute<Ak::TransformAttribute>(10.0f, 10.0f, 1.0f);
	cube.addAttribute<Ak::ModelAttribute>(Ak::createQuad());
}
