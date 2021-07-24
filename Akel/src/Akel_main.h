// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 24/07/2021

#ifndef __AK_MAIN__
#define __AK_MAIN__

#include <Akpch.h>
#include <Core/application.h>
#include <Core/softwareInfo.h>

extern Ak::Application* Akel_main();

int main(int argc, char** argv)
{
	Ak::Core::log::Init();
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

	#ifdef AK_USE_MEMORY_HELPER
		Ak::InitMemoryHelper();
	#endif

	AK_BEGIN_SESSION("Start");
		auto app = Akel_main();
	AK_END_SESSION();

	AK_BEGIN_SESSION("Runtime");
		app->run();
	AK_END_SESSION();

	AK_BEGIN_SESSION("Shutdown");
		delete app;
	AK_END_SESSION();

	#ifdef AK_USE_MEMORY_HELPER
		Ak::EndMemoryHelper();
	#endif

	std::cout << Ak::bg_green << "Akel successfully finished" << Ak::bg_def << std::endl;

	return 0;
}

#endif // __AK_MAIN__
