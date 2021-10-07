// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 07/10/2021

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
		#ifdef AK_PROJECT_FILE_DIR
			Ak::Core::ProjectFile::setDir(AK_PROJECT_FILE_DIR);
		#endif
		#ifdef AK_PROJECT_FILE_NAME
			Ak::Core::ProjectFile::setName(AK_PROJECT_FILE_NAME);
		#endif
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
