#include <Akel.h>
#include <Akel_main.h>

class Transformations : public Ak::Component
{
	public:
		void update() override
		{
			float x = 0.5 * (sin(2 * _time + 2) + sin(_time * M_PI - 2));
			float y = 0.6 * (sin(2 * _time + 4) + sin(_time * M_PI - 1.76));
			float z = 0.3 * (sin(2 * _time - 2) + sin(_time * M_PI - 1.2));
			Ak::Matrixes::rotate3D(_angle, x, y, z);
			_time += 0.01f;
		}

	private:
		float _angle = 0.075f;
		float _time = 0.0f;
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
	app->add_component<Ak::Camera3D>(0, 2, 0);
	app->add_component<Transformations>();
	Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene");
	scene->add_3D_entity({ Models::cube, { -0.5f, -0.5f, -0.5f }, { 1.f, 1.f, 1.f }, Colors::none, Ak::Res::get().getTexturesPath() / "rodriguez.jpg" });
	app->add_scene(scene);
	return app;
}
