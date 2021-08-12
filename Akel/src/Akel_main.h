// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 12/08/2021

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

		Ak::Core::log::Init();
		Ak::Conf_manager::load(Ak::Core::ProjectFile::getDirFileProject() + Ak::Core::ProjectFile::getNameFileProject() + std::string(".akel"));

		if(Ak::Conf_manager::getBoolValue("use_memory_manager"))
			Ak::MemoryManager::init();

		Ak::AudioManager::initAudioManager();

		auto app = Akel_main();
	AK_END_SESSION();

	AK_BEGIN_SESSION("Runtime");
		app->run();
	AK_END_SESSION();

	AK_BEGIN_SESSION("Shutdown");
		bool freed = false;
		for(auto jam : Ak::JamAllocator::allAllocs)
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
			for(auto fixed : Ak::FixedAllocator::allAllocs)
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

		if(Ak::Conf_manager::getBoolValue("use_memory_manager"))
			Ak::MemoryManager::end();

		Ak::Core::ProjectFile::initProjFile();
	AK_END_SESSION();

	std::cout << Ak::bg_green << "Akel successfully finished" << Ak::bg_def << std::endl;

	return 0;
}

#endif // __AK_MAIN__
