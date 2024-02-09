// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 08/02/2024

#include <Drivers/SDL2/SDL2Module.h>
#include <Core/Logs.h>

namespace Ak
{
	SDL2Module* SDL2Module::s_instance = nullptr;

	SDL2Module::SDL2Module() : Module("SDL2Module")
	{
		if(s_instance != nullptr)
			FatalError("only one instance of SDL2Module can exist at a given time");
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
			FatalError("SDL error : unable to init all subsystems : %", SDL_GetError());
		s_instance = this;
	}

	SDL2Module& SDL2Module::Get()
	{
		Assert(s_instance != nullptr, "SDL2Module has not been instanciated");
		return *s_instance;
	}

	SDL2Module::~SDL2Module()
	{
		SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
		SDL_Quit();
		s_instance = nullptr;
	}
}
