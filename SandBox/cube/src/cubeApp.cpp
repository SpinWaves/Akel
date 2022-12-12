#include <Akel.h>
#include <Akel_main.h>

class FPSprinterComponent : public Ak::Component
{
    public:
        void update() override { std::cout << "fps : " << Ak::CounterFPS::getFPS() << " - ticks : " << Ak::CounterFPS::getTicks() << '\r' << std::flush; }
};

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
        instance.project_file_path = Ak::Core::getMainDirPath() + "../../SandBox/cube";
        instance.project_file_name = "cube";
    return instance;
}

Ak::Application* Akel_mainApp()
{
	Ak::Application* app = Ak::memAlloc<Ak::Application>();

	Ak::WindowComponent* window = app->add_component<Ak::WindowComponent>();
	window->title = "Cube using Akel Engine";
	window->fetchSettings();

	app->add_component<FPSprinterComponent>();
	app->add_component<Ak::RendererComponent>(window);

	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene", window);

	scene->loadCustomShader(Ak::Core::getMainDirPath() + "../../SandBox/cube/src/vert.spv");
	scene->loadCustomShader(Ak::Core::getMainDirPath() + "../../SandBox/cube/src/frag.spv");

	scene->add_3D_entity({ Models::quad, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }, Colors::red });

	Ak::SceneManager* scenes_manager = app->add_component<Ak::SceneManager>();
	scenes_manager->add_scene(scene);

	return app;
}
