#include <Akel.h>
#include <Akel_main.h>

class TitleComponent : public Ak::Component
{
	public:
		TitleComponent() : Component("title_component") {}
		void onFixedUpdate() override
		{
			static Ak::WindowComponent* window = Ak::getMainAppComponentStack()->get_component_as<Ak::WindowComponent*>("__window_component");
			static Ak::RendererComponent* renderer = Ak::getMainAppComponentStack()->get_component_as<Ak::RendererComponent*>("__renderer_component0");
			window->title = "Scripting using Akel Engine, FPS : " + std::to_string(renderer->getFPS());
			window->fetchSettings();
		}
};

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
        instance.project_file_name = "script";
    return instance;
}

Ak::Application* Akel_mainApp(Ak::CommandLineArgs args)
{
	Ak::PlainApplication* app = Ak::memAlloc<Ak::PlainApplication>("Scripting using Akel Engine");
	app->add_component<TitleComponent>();
	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene");
	scene->addCamera<Ak::Cam::FirstPerson3D>(-5.0f, 1.0f, 0.0f);
	app->add_scene(scene);

	// Setting up LEM model and material
	Ak::MaterialDesc lem_material_desc;
	lem_material_desc.albedo = Ak::VFS::resolve("//Textures/apollo_map.jpg");
	Ak::MaterialID lem_material = Ak::addMaterialToLibrary(lem_material_desc);

	Ak::Entity lem = scene->createEntity();
	lem.addAttribute<Ak::TransformAttribute>(0.0f, 0.0f, 0.0f);
	lem.addAttribute<Ak::ModelAttribute>(Ak::VFS::resolve("//Meshes/apollo_lunar_module.obj"), lem_material);
	lem.getAttribute<Ak::TransformAttribute>().scale = Ak::Maths::Vec3f(0.02f, 0.02f, 0.02f);

	Ak::LuaLoader lua(app, *app->getSceneManager());
	lem.addAttribute<Ak::ScriptAttribute>(lua.loadScript(Ak::VFS::resolve("//Scripts/lem_script.lua")));

	Ak::Scene* scene2 = Ak::memAlloc<Ak::Scene>("second scene");
	scene2->addCamera<Ak::Cam::FirstPerson3D>(0.0f, 0.0f, 0.0f);
	app->add_scene(scene2);

	// Setting up Knuckles model and material
	Ak::MaterialDesc knuckles_material_desc;
	knuckles_material_desc.albedo = Ak::VFS::resolve("//Textures/knuckles.png");
	Ak::MaterialID knuckles_material = Ak::addMaterialToLibrary(knuckles_material_desc);

	Ak::Entity knuckles = scene2->createEntity();
	knuckles.addAttribute<Ak::TransformAttribute>(0.0f, 0.0f, 0.0f);
	knuckles.addAttribute<Ak::ModelAttribute>(Ak::VFS::resolve("//Meshes/knuckles.obj"), knuckles_material);
	knuckles.addAttribute<Ak::ScriptAttribute>(lua.loadScript(Ak::VFS::resolve("//Scripts/knuckles_script.lua")));

	return app;
}
