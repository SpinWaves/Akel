#include <Akel.h>
#include <Akel_main.h>
#include "comp.h"

class App : public Ak::Application
{
    public:
        explicit App() : Ak::Application("Kila test")
        {
            add_component(Ak::custom_malloc<Comp>());
        }
        ~App() = default;
};

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
		instance.project_file_path = std::string(Ak::Core::getMainDirPath() + "Tests/Kila");
		instance.project_file_name = "app";
    return instance;    
}

Ak::Application* Akel_mainApplication()
{
    return Ak::custom_malloc<App>();
}