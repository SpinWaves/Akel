// This file is a part of Akel
// CREATED : 29/04/2021
// UPDATED : 29/04/2021

#include <Platform/platform.h>
#include <Utils/utils.h>

namespace Ak
{
	void exit()
	{
		SDL_Quit();
		std::cout << bg_green << "Akel successfully exited" << bg_def << std::endl;
	}
}

