#include <Akel.h>
#include <Akel_main.h>
#include "comp.h"

class App : public Ak::Application
{
    public:
        explicit App() : Ak::Application("Kila test")
        {
            add_component<Comp>();
        }
        ~App() = default;
};

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
		instance.project_file_path = std::string(Ak::Core::getMainDirPath() + "Tests/Kila");
		instance.project_file_name = "app";
		instance.enable_warning_console_message = true;
        instance.use_memory_manager = true;
    return instance;    
}

Ak::Application* Akel_mainApplication()
{
    return Ak::memAlloc<App>();
}
