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
	Ak::PlainApplication* app = Ak::memAlloc<Ak::PlainApplication>("Rectangle using Akel Engine");
	app->add_component<FPSprinterComponent>();

	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene", app->getWindow());

	scene->loadCustomShader(Ak::Core::getMainDirPath() + "../../SandBox/rect/src/vert_u.spv");
	scene->loadCustomShader(Ak::Core::getMainDirPath() + "../../SandBox/rect/src/frag_u.spv");

	scene->add_2D_entity({ Models::quad, { 100.f, 100.f }, { 200.f, 200.f }, Colors::red });
	app->add_scene(scene);

	return app;
}
