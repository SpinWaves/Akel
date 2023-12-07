// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/09/2023
// Updated : 02/12/2023

#include <Core/engine.h>
#include <Core/vfs.h>
#include <Renderer/Core/render_core.h>
#include <Core/Memory/memoryManager.h>

extern void Akel_InstanceSetup(Ak::AkelInstance& instance); // defined in user application
extern void Akel_AppSetup(Ak::Application& app, Ak::CommandLineArgs args); // same

namespace Ak
{
	namespace Core::log::internal
	{
		void init(std::filesystem::path path);
	}
	namespace Core::memory::internal
	{
		void end();
	}

	namespace internal
	{
		class FatalErrorEvent : public BaseEvent
		{
			public:
				FatalErrorEvent() = default;
				uint32_t what() const override { return 167; }
				~FatalErrorEvent() = default;
		};
	}

	void Engine::init(int ac, char** av)
	{
		VFS::init(av[0]);
		Core::log::internal::init(av[0]);
		AK_BEGIN_SESSION("Startup");
			func::function<void(const BaseEvent&)> functor = [=](const BaseEvent& event)
			{
				if(event.what() == 167)
					fatalErrorEventHandle();
			};
			EventBus::registerListener({ functor, "__engine" });
			Akel_InstanceSetup(_instance);
			if(!initAkel(&_instance))
				Core::log::report(FATAL_ERROR, "Something went wrong with Akel initialisation");
			_app.init();
			Akel_AppSetup(_app, { av, ac });
		AK_END_SESSION();
	}

	void Engine::run()
	{
		AK_BEGIN_SESSION("Runtime");
			_app.run();
		AK_END_SESSION();
	}

	void Engine::destroy()
	{
		AK_BEGIN_SESSION("Shutdown");
			_app.destroy();
			Render_Core::get().destroy();
			_instance.writeProjectFile();
			Core::memory::internal::end();
		AK_END_SESSION();

		if(_instance.at_akel_exit)
			_instance.at_akel_exit();
		std::cout << Ak::bg_green << "Akel successfully finished" << Ak::bg_def << std::endl;
	}

	void Engine::fatalErrorEventHandle()
	{
		EventBus::send("__internal_memory_manager", internal::FatalErrorEvent{});
		std::exit(0);
	}
}
