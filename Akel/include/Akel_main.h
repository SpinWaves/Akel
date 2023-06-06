// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 07/06/2023

#ifndef __AK_MAIN__
#define __AK_MAIN__

#include <Core/application.h>
#include <Akpch.h>
#include <Core/vfs.h>
#include <Core/instance.h>

extern Ak::AkelInstance Akel_init();
extern Ak::Application* Akel_mainApp(Ak::CommandLineArgs args);

int main(int argc, char** argv)
{
	Ak::VFS::init(argv[0]);
	Ak::Core::log::init(argv[0]);

	AK_BEGIN_SESSION("Startup");
		Ak::AkelInstance project = std::move(Akel_init());
		if(!Ak::initAkel(&project))
			Ak::Core::log::report(FATAL_ERROR, "Something went wrong with Akel initialisation");
		auto app = Akel_mainApp({ argv, argc });
	AK_END_SESSION();

	AK_BEGIN_SESSION("Runtime");
		app->run();
	AK_END_SESSION();

	AK_BEGIN_SESSION("Shutdown");
		app->destroy();
		Ak::memFree(app);
		Ak::Render_Core::get().destroy();
		project.writeProjectFile();
		Ak::MemoryManager::end();
	AK_END_SESSION();

	if(project.at_akel_exit)
		project.at_akel_exit();
	std::cout << Ak::bg_green << "Akel successfully finished" << Ak::bg_def << std::endl;

	return 0;
}

#endif // __AK_MAIN__
