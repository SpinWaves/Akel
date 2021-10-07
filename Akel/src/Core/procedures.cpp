// This file is a part of Akel
// CREATED : 06/10/2021
// UPDATED : 07/10/2021

#include <Core/core.h>
#include <Audio/audio.h>
#include <Shaders/build.h>

namespace Ak
{
    bool initAkel()
    {
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

		Ak::Core::ProjectFile::initProjFile();

		Ak::MemoryManager::init();

		Ak::AudioManager::initAudioManager();

		Ak::buildBasics2D();

    }
}
