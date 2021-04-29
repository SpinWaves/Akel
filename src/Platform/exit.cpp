// This file is a part of AtlasEngine
// CREATED : 29/04/2021
// UPDATED : 29/04/2021

#include <Platform/platform.h>
#include <Utils/utils.h>

namespace AE
{
	void exit()
	{
		SDL_Quit();
		std::cout << bg_green << "AtlasEngine successfully exited" << bg_def << std::endl;
	}
}

