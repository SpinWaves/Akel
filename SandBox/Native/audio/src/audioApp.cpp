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
			window->title = "Audio using Akel Engine, FPS : " + std::to_string(renderer->getFPS());
			window->fetchSettings();
		}
};

void Akel_InstanceSetup(Ak::AkelInstance& instance)
{
	instance.project_file_name = "audio";
}

void Akel_AppSetup(Ak::Application& app, Ak::CommandLineArgs args)
{
	Ak::PlainApplication papp(app, "Audio using Akel Engine");
	papp.add_component<Ak::AudioComponent>();
	papp.add_component<TitleComponent>();
	papp.add_component<Ak::ImGuiRenderStats>(papp.getRenderer());

	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main_scene");
	scene->addCamera<Ak::Cam::FirstPerson3D>(-5.0f, 1.0f, 0.0f);
	papp.add_scene(scene);

	// Setting up Spaceship model and material
	Ak::MaterialDesc spaceship_material_desc;
	spaceship_material_desc.albedo = Ak::VFS::resolve("//Textures/spaceship_map.jpg");
	Ak::MaterialID spaceship_material = Ak::addMaterialToLibrary(spaceship_material_desc);

	Ak::Entity spaceship = scene->createEntity();
	spaceship.addAttribute<Ak::TransformAttribute>(0.0f, 0.0f, 0.0f);
	spaceship.addAttribute<Ak::AudioAttribute>(Ak::VFS::resolve("//Sounds/engine.ogg"));
	spaceship.addAttribute<Ak::ModelAttribute>(Ak::VFS::resolve("//Meshes/spaceship.obj"), spaceship_material);

	Ak::LuaLoader lua(&app, *papp.getSceneManager());
	spaceship.addAttribute<Ak::ScriptAttribute>(lua.loadScript(Ak::VFS::resolve("//Scripts/spaceship_script.lua")));
}
