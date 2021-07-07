// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 07/07/2021

#ifndef __AK_MAIN__
#define __AK_MAIN__

#include <Akpch.h>
#include <Core/application.h>
#include <Core/softwareInfo.h>

extern Ak::Application* Akel_main();

int main(int argc, char** argv)
{
	Ak::Core::log::Init();

	AK_BEGIN_SESSION("Start");
		Ak::Core::printEngineInfo();
		auto app = Akel_main();
	AK_END_SESSION();

	AK_BEGIN_SESSION("Runtime");
		app->run();
	AK_END_SESSION();

	AK_BEGIN_SESSION("Shutdown");
		delete app;
	AK_END_SESSION();

	return 0;
}

#endif // __AK_MAIN__

