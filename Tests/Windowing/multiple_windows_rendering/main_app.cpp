#include <Akel.h>
#include <Akel_main.h>

class App : public Ak::Application
{
	public:
		App() : Ak::Application()
		{
			Ak::WindowComponent* win1 = Ak::memAlloc<Ak::WindowComponent>();
			add_component(win1);
			win1->title = "Window 1";
			win1->size.SET(1280, 720);
			win1->resizable = true;
			win1->fetchSettings();

			Ak::WindowComponent* win2 = Ak::memAlloc<Ak::WindowComponent>();
			add_component(win2);
			win2->title = "Window 2";
			win2->size.SET(1280, 720);
			win2->resizable = true;
			win2->fetchSettings();

			Ak::WindowComponent* win3 = Ak::memAlloc<Ak::WindowComponent>();
			add_component(win3);
			win3->title = "Window 3";
			win3->size.SET(1280, 720);
			win3->resizable = true;
			win3->fetchSettings();

			add_component<Ak::RendererComponent>(win1);
            Ak::Render_Core::get().getClearValue().color.float32[0] = 128 / 255;
            Ak::Render_Core::get().getClearValue().color.float32[1] = 175 / 255;
            Ak::Render_Core::get().getClearValue().color.float32[2] = 255 / 255;
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
