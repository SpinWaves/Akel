// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/SDL2/SDL2Module.h>
#include <Core/Logs.h>
#include <Config.h>

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

		/* Remove this comment if you want to prioritise Wayland over X11/XWayland, at your own risks */
		//SDL_SetHint(SDL_HINT_VIDEODRIVER, "wayland,x11");
	}

	std::string SDL2Module::GetEngineModuleVersion()
	{
		return AKEL_VERSION;
	}

	SDL2Module& SDL2Module::Get()
	{
		Assert(s_instance != nullptr, "SDL2Module has not been instanciated");
		return *s_instance;
	}

	SDL2Module::~SDL2Module()
	{
		Module::~Module();
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		SDL_QuitSubSystem(SDL_INIT_TIMER);
		SDL_QuitSubSystem(SDL_INIT_EVENTS);
		SDL_Quit();
		s_instance = nullptr;
	}
}
