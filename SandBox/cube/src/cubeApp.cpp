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

	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene");

	scene->loadCustomShader<Ak::shaderlang::nzsl>(Ak::Res::get().getScriptsPath() / "vert.nzsl");
	scene->loadCustomShader<Ak::shaderlang::nzsl>(Ak::Res::get().getScriptsPath() / "frag.nzsl");

	scene->add_3D_entity({ Models::cube, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }, Colors::red, Ak::Res::get().getTexturesPath() / "rodriguez.jpg" });
	app->add_scene(scene);

	return app;
}
