#include <Akel.h>
#include <Akel_main.h>

class Rect : public Ak::Application
{
    public:
        explicit Rect() : Ak::Application("Rect")
        {
            Ak::WindowComponent* window = Ak::custom_malloc<Ak::WindowComponent>();
            add_component(window); // inherited from Ak::Application
            window->setSetting(Ak::winsets::title, "Rectangle using Akel Engine");
            //window->setSetting(Ak::winsets::size, 1280, 750);
            window->setSetting(Ak::winsets::resizable, false);

            add_component(Ak::custom_malloc<Ak::RendererComponent>(window->getNativeWindow()));
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
    return Ak::custom_malloc<Rect>();
}
