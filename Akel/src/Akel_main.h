// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 30/05/2022

#ifndef __AK_MAIN__
#define __AK_MAIN__

#include <Core/application.h>
#include <Akpch.h>
#include <Core/paths.h>
#include <Core/parameterStruct.h>

extern Ak::AkelInstance Akel_init();
extern Ak::Application* Akel_mainApplication();

int main(int argc, char** argv)
{
	Ak::Core::log::Init();

	AK_BEGIN_SESSION("Start");
		Ak::AkelInstance project = std::move(Akel_init());
		if(!Ak::initAkel(&project))
			Ak::Core::log::report(FATAL_ERROR, "Something went wrong with Akel initialisation");
		auto app = Akel_mainApplication();
	AK_END_SESSION();

	AK_BEGIN_SESSION("Runtime");
		app->run();
	AK_END_SESSION();

	AK_BEGIN_SESSION("Shutdown");
		Ak::memFree(app);
		Ak::MemoryManager::end();
	AK_END_SESSION();

	std::cout << Ak::bg_green << "Akel successfully finished" << Ak::bg_def << std::endl;

	return 0;
}

#endif // __AK_MAIN__
