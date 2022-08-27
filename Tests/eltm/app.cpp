#include <Akel.h>
#include <Akel_main.h>

class ELTM_tester_comp : public Ak::Component
{
	public:
		ELTM_tester_comp() : Ak::Component("eltm tester") {}

        void update() override
		{
			Ak::ELTM eltm;

			eltm.load(Ak::Core::getMainDirPath() + "test.eltm");
			std::cout << eltm.getText("test") << std::endl;
			std::cout << eltm.getText("test2") << std::endl;
			std::cout << eltm.getText("myModule.oui") << std::endl;
		}

        void onEvent(Ak::Input& input) override
		{
			input.finish();
		}
};

class App : public Ak::Application
{
    public:
        App() : Ak::Application()
        {
			add_component<ELTM_tester_comp>();
        }
        ~App() = default;
};

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
		instance.project_file_path = Ak::Core::getMainDirPath();
		instance.project_file_name = "app";
		instance.enable_warning_console_message = true;
        instance.use_memory_manager = true;
    return instance;    
}

Ak::Application* Akel_mainApplication()
{
    return Ak::memAlloc<App>();
}
