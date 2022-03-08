#include <Akel.h>
#include <Akel_main.h>

class FPSprinterComponent : public Ak::Component
{
    public:
        void update() override { std::cout << "fps : " << Ak::CounterFPS::getFPS() << " - ticks : " << Ak::CounterFPS::getTicks() << '\r' << std::flush; }
};

class Cube : public Ak::Application
{
    public:
        explicit Cube() : Ak::Application("Cube")
        {
            Ak::WindowComponent* window = Ak::memAlloc<Ak::WindowComponent>();
            add_component(window); // function inherited from Ak::Application
            window->setSetting(Ak::winsets::title, "Cube using Akel Engine");
            window->setSetting(Ak::winsets::resizable, true);
            window->setSetting(Ak::winsets::vsync, false);
            window->setSetting(Ak::winsets::size, 1280, 750);

            add_component<FPSprinterComponent>();
            add_component<Ak::Camera3D>(-1, -1, 10);

            Ak::RendererComponent* renderer = Ak::memAlloc<Ak::RendererComponent>(window, Ak::shader::basic_3D);
            add_component(renderer);
            renderer->setBackgroundColor(0.49f, 0.66f, 0.85f, 1.0f);

            Ak::Entity2D rectangle(Models::quad, {0.0f, 0.0f}, {1.0f, 5.0f}, Colors::black);
            Ak::Entity2D rectangle2(Models::quad, {1.0f, 0.0f}, {1.0f, 5.0f}, Colors::yellow);
            Ak::Entity2D rectangle3(Models::quad, {2.0f, 0.0f}, {1.0f, 5.0f}, Colors::red);
            
            renderer->add_entity(rectangle);
            renderer->add_entity(rectangle2);
            renderer->add_entity(rectangle3);

            renderer->recreateRenderer();
        }
        ~Cube() = default;
};

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
        instance.project_file_path = Ak::Core::getMainDirPath() + "SandBox/cube";
        instance.project_file_name = "cube";
        instance.memory_manager_enable_fixed_allocator = false;
    return instance;    
}

Ak::Application* Akel_mainApplication()
{
    return Ak::memAlloc<Cube>();
}
