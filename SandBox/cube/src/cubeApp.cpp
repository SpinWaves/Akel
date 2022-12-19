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
	Ak::PlainApplication* app = Ak::memAlloc<Ak::PlainApplication>("Cube using Akel Engine");
	app->getWindow()->vsync = false;
	app->getWindow()->fetchSettings();
	app->add_component<FPSprinterComponent>();
	app->add_component<Ak::Camera3D>(0, 2, 0);

	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene", app->getWindow());

	scene->loadCustomShader(Ak::Core::getMainDirPath() + "../../SandBox/cube/src/vert_u.spv");
	scene->loadCustomShader(Ak::Core::getMainDirPath() + "../../SandBox/cube/src/frag_u.spv");

	scene->add_3D_entity({ Models::cube, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }, Colors::red });
	app->add_scene(scene);

	return app;
}
