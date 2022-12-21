#include <Akel.h>
#include <Akel_main.h>

class App : public Ak::Application
{
	public:
		App() : Ak::Application()
		{
			Ak::WindowComponent* win1 = add_component<Ak::WindowComponent>();
			win1->title = "Window 1";
			win1->size.SET(1280, 720);
			win1->resizable = true;
			win1->fetchSettings();

			Ak::WindowComponent* win2 = add_component<Ak::WindowComponent>();
			win2->title = "Window 2";
			win2->size.SET(1280, 720);
			win2->resizable = true;
			win2->fetchSettings();

			Ak::WindowComponent* win3 = add_component<Ak::WindowComponent>();
			win3->title = "Window 3";
			win3->size.SET(1280, 720);
			win3->resizable = true;
			win3->fetchSettings();

			auto renderer1 = add_component<Ak::RendererComponent>(win1);
			auto scene_manager1 = add_component<Ak::SceneManager>(renderer1);
			add_component<Ak::Camera3D>(0, 2, 0);
			Ak::Scene* scene1 = Ak::memAlloc<Ak::Scene>("main scene 1");
			scene1->loadCustomShader(Ak::Core::getMainDirPath() + "../../../SandBox/cube/src/vert_u.spv");
			scene1->loadCustomShader(Ak::Core::getMainDirPath() + "../../../SandBox/cube/src/frag_u.spv");
			scene1->add_3D_entity({ Models::cube, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }, Colors::red });
			scene_manager1->add_scene(scene1);

			auto renderer2 = add_component<Ak::RendererComponent>(win2);
			auto scene_manager2 = add_component<Ak::SceneManager>(renderer2);
			Ak::Scene* scene2 = Ak::memAlloc<Ak::Scene>("main scene 2");
			scene2->loadCustomShader(Ak::Core::getMainDirPath() + "../../../SandBox/cube/src/vert_u.spv");
			scene2->loadCustomShader(Ak::Core::getMainDirPath() + "../../../SandBox/cube/src/frag_u.spv");
			scene2->add_2D_entity({ Models::quad, { 100.f, 100.f }, { 400.f, 400.f }, Colors::red });
			scene_manager2->add_scene(scene2);

			auto renderer3 = add_component<Ak::RendererComponent>(win3);
			auto scene_manager3 = add_component<Ak::SceneManager>(renderer3);
			Ak::Scene* scene3 = Ak::memAlloc<Ak::Scene>("main scene 3");
			scene3->loadCustomShader(Ak::Core::getMainDirPath() + "../../../SandBox/cube/src/vert_u.spv");
			scene3->loadCustomShader(Ak::Core::getMainDirPath() + "../../../SandBox/cube/src/frag_u.spv");
			scene3->add_2D_entity({ Models::quad, { 500.f, 500.f }, { 200.f, 200.f }, Colors::red });
			scene_manager3->add_scene(scene3);
		}

		~App() = default;
};

Ak::AkelInstance Akel_init()
{
    Ak::AkelInstance instance;
		instance.project_file_path = Ak::Core::getMainDirPath();
		instance.project_file_name = "app";
		instance.enable_warning_console_message = true;
    return instance;    
}

Ak::Application* Akel_mainApp()
{
    return Ak::memAlloc<App>();
}
