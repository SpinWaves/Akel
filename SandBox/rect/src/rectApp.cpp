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
        explicit Rect() : Ak::Application("Rect")
        {
            Ak::WindowComponent* window = Ak::memAlloc<Ak::WindowComponent>();
            add_component(window); // function inherited from Ak::Application
            window->setSetting(Ak::winsets::title, "Rectangle using Akel Engine");
            window->setSetting(Ak::winsets::resizable, false);
            //window->setSetting(Ak::winsets::size, 1280, 750);

            add_component<FPSprinterComponent>();

            Ak::RendererComponent* renderer = Ak::memAlloc<Ak::RendererComponent>(window->getNativeWindow(), Ak::shader::basic_2D);
            renderer->setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            Ak::Entity2D rectangle(Models::quad, {-0.5f, -0.5f}, {1.0f, 1.0f}, Colors::red);
            renderer->add_entity(rectangle);
            add_component(renderer);
        }
        ~Rect() = default;
};

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
        instance.project_file_path = Ak::Core::getMainDirPath() + "SandBox/rect";
        instance.project_file_name = "rect";
        instance.memory_manager_enable_fixed_allocator = false;
    return instance;    
}

Ak::Application* Akel_mainApplication()
{
    return Ak::memAlloc<Rect>();
}
