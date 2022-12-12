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
        instance.project_file_path = Ak::Core::getMainDirPath() + "../../SandBox/rect";
        instance.project_file_name = "rect";
    return instance;
}

Ak::Application* Akel_mainApp()
{
	Ak::Application* app = Ak::memAlloc<Ak::Application>();

	Ak::WindowComponent* window = app->add_component<Ak::WindowComponent>();
	window->title = "Rectangle using Akel Engine";
	window->fetchSettings();

	app->add_component<FPSprinterComponent>();
	app->add_component<Ak::RendererComponent>(window);

	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene", window);

	scene->loadCustomShader(Ak::Core::getMainDirPath() + "../../SandBox/rect/src/vert_u.spv");
	scene->loadCustomShader(Ak::Core::getMainDirPath() + "../../SandBox/rect/src/frag_u.spv");

	scene->add_2D_entity({ Models::quad, { -500.f, -500.f }, { 1000.f, 1000.f }, Colors::red });

	Ak::SceneManager* scenes_manager = app->add_component<Ak::SceneManager>();
	scenes_manager->add_scene(scene);

	return app;
}
