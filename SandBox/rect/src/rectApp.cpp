#include <Akel.h>
#include <Akel_main.h>

class FPSprinterComponent : public Ak::Component
{
    public:
        void update() override { Ak::CounterFPS::printTicks(); Ak::CounterFPS::printFPS(); }
};

class Rect : public Ak::Application
{
    public:
        explicit Rect() : Ak::Application("Rect")
        {
            Ak::WindowComponent* window = Ak::memAlloc<Ak::WindowComponent>();
            add_component(window); // function inherited from Ak::Application
            window->setSetting(Ak::winsets::title, "Rectangle using Akel Engine");
            //window->setSetting(Ak::winsets::size, 1280, 750);
            window->setSetting(Ak::winsets::resizable, false);

            add_component<Ak::RendererComponent>(window->getNativeWindow());
            add_component<FPSprinterComponent>();
        }
        ~Rect() = default;
};

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
		instance.project_file_path = std::string(Ak::Core::getMainDirPath() + "SandBox/rect");
		instance.project_file_name = "rect";
    return instance;    
}

Ak::Application* Akel_mainApplication()
{
    return Ak::memAlloc<Rect>();
}
