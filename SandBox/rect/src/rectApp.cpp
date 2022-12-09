#include <Akel.h>
#include <Akel_main.h>

class FPSprinterComponent : public Ak::Component
{
    public:
        void update() override { std::cout << "fps : " << Ak::CounterFPS::getFPS() << " - ticks : " << Ak::CounterFPS::getTicks() << '\r' << std::flush; }
};

class Rect : public Ak::Application
{
    public:
        Rect() : Ak::Application()
        {
            Ak::WindowComponent* window = Ak::memAlloc<Ak::WindowComponent>();
            add_component(window); // function inherited from Ak::Application
            window->title = "Rectangle using Akel Engine";
            window->resizable = true;
            window->vsync = false;
            window->size.SET(1280, 750);
            window->fetchSettings();

            add_component<FPSprinterComponent>();
            add_component<Ak::RendererComponent>(window);

			Ak::Scene* scene = Ak::memAlloc<Ak::Scene>("main scene", window);

			scene->loadCustomShader(Ak::Core::getMainDirPath() + "../../SandBox/rect/src/vert_u.spv");
			scene->loadCustomShader(Ak::Core::getMainDirPath() + "../../SandBox/rect/src/frag_u.spv");

			Ak::Entity2D rectangle(Models::quad, { -0.5f, -0.5f }, { 1.f, 1.f }, Colors::red);
			scene->add_2D_entity(std::move(rectangle));

			Ak::SceneManager* scenes_manager = Ak::memAlloc<Ak::SceneManager>();
			scenes_manager->add_scene(scene);

			add_component(scenes_manager);
        }
        ~Rect() = default;
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
	return Ak::memAlloc<Rect>();
}
