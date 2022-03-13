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
            window->title = "Rectangle using Akel Engine";
            window->resizable = true;
            window->vsync = false;
            window->size.SET(1280, 750);
            window->fetchSettings();

            add_component<FPSprinterComponent>();

            Ak::RendererComponent* renderer = Ak::memAlloc<Ak::RendererComponent>(window, Ak::shader::basic_2D);
            renderer->setRenderingMode(Ak::RenderingMode::render2D);
            renderer->setBackgroundColor(0.49f, 0.66f, 0.85f, 1.0f);

            Ak::Entity2D rectangle(Models::quad, {50.0f, 50.0f}, {250.0f, 200.0f}, Colors::red);
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
