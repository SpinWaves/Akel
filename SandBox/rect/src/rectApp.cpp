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
        instance.project_file_path = Ak::Core::getMainDirPath();
        instance.project_file_name = "rect";
    return instance;
}

Ak::Application* Akel_mainApp()
{
	Ak::PlainApplication* app = Ak::memAlloc<Ak::PlainApplication>("Rectangle using Akel Engine");
	app->add_component<FPSprinterComponent>();

	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene");

	scene->loadCustomShader(Ak::Core::getMainDirPath() + "src/vert.spv");
	scene->loadCustomShader(Ak::Core::getMainDirPath() + "src/frag.spv");

	scene->add_2D_entity({ Models::quad, { 100.f, 100.f }, { 200.f, 200.f }, Colors::none, Ak::Res::get().getTexturesPath() / "rodriguez.jpg" });
	app->add_scene(scene);

	return app;
}
