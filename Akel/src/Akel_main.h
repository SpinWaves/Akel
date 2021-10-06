// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 05/10/2021

#ifndef __AK_MAIN__
#define __AK_MAIN__

#include <Core/application.h>
#include <Akpch.h>
#include <Core/paths.h>

extern Ak::Application* Akel_main();

int main(int argc, char** argv)
{
	Ak::Core::Paths::initPaths();
	Ak::Core::log::Init();

	AK_BEGIN_SESSION("Start");
		Ak::initAkel();
		auto app = Akel_main();
	AK_END_SESSION();

	AK_BEGIN_SESSION("Runtime");
		app->run();
	AK_END_SESSION();

	AK_BEGIN_SESSION("Shutdown");
		Ak::custom_free(app);
		Ak::AudioManager::shutdownAudioManager();
		Ak::MemoryManager::end();
	AK_END_SESSION();

	std::cout << Ak::bg_green << "Akel successfully finished" << Ak::bg_def << std::endl;

	return 0;
}

#endif // __AK_MAIN__
