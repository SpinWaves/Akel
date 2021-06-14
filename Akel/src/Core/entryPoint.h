// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 14/06/2021

#ifndef __AK_ENTRY_POINT__
#define __AK_ENTRY_POINT__

#include <Akpch.h>
#include <Core/application.h>

extern Ak::Application* Akel_main();

int main(int argc, char** argv)
{
	auto app = Akel_main();
	app->addComponent<Ak::Window>();
	delete app;

	return 0;
}

#endif // __AK_ENTRY_POINT__

