// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 10/09/2021

#ifndef __AK_MAIN__
#define __AK_MAIN__

#include <Core/application.h>
#include <Akpch.h>
#include <Core/softwareInfo.h>
#include <Core/paths.h>
#include <Audio/audio.h>

extern Ak::Application* Akel_main();

int main(int argc, char** argv)
{
	Ak::Core::Paths::initPaths();
	Ak::Core::log::Init();

	AK_BEGIN_SESSION("Start");
		#if defined(AK_64BITS)
			if(sizeof(void*) != 8)
			{
				Ak::Core::log::report(ERROR, "Conflict of system architecture detection");
			    return 1;
			}
			Ak::Core::log::report("architecture: 64bits");
		#elif defined(AK_32BITS)
			if(sizeof(void*) != 4)
			{
				Ak::Core::log::report(ERROR, "Conflict of system architecture detection");
			    return 1;
			}
			Ak::Core::log::report("architecture: 32bits");
		#endif

		#ifdef AK_PROJECT_FILE_DIR
			Ak::Core::ProjectFile::setDir(AK_PROJECT_FILE_DIR);
		#endif
		#ifdef AK_PROJECT_FILE_NAME
			Ak::Core::ProjectFile::setName(AK_PROJECT_FILE_NAME);
		#endif

		Ak::Core::ProjectFile::initProjFile();

		Ak::MemoryManager::init();

		Ak::AudioManager::initAudioManager();

		auto app = Akel_main();
	AK_END_SESSION();

	AK_BEGIN_SESSION("Runtime");
		app->run();
	AK_END_SESSION();

	AK_BEGIN_SESSION("Shutdown");
		bool freed = false;
		for(auto jam : Ak::MemoryManager::accesToControlUnit()->jamStack)
		{
			if(jam->contains(app))
			{
				jam->free(app);
				freed = true;
				break;
			}
		}
		if(!freed)
		{
			for(auto fixed : Ak::MemoryManager::accesToControlUnit()->fixedStack)
			{
				if(fixed->contains(app))
				{
					fixed->free(app);
					freed = true;
					break;
				}
			}
			if(!freed)
				delete app;
		}

		Ak::AudioManager::shutdownAudioManager();

		Ak::MemoryManager::end();
	AK_END_SESSION();

	std::cout << Ak::bg_green << "Akel successfully finished" << Ak::bg_def << std::endl;

	return 0;
}

#endif // __AK_MAIN__
