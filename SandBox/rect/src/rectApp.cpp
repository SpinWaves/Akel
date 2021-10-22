#include <Akel.h>
#include <Akel_main.h>
#include "rectComponent.h"

class Rect : public Ak::Application
{
    public:
        explicit Rect() : Ak::Application("Rect")
        {
            add_component(Ak::custom_malloc<RectComponent>());
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
