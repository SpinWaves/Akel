// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/02/2024
// Updated : 08/02/2024

#ifndef __AK_DRIVERS_SDL2_MODULE__
#define __AK_DRIVERS_SDL2_MODULE__

#include <Drivers/SDL2/PreCompiled.h>
#include <Core/Module.h>
#include <Utils/TypeList.h>

namespace Ak
{
	class AK_SDL2_API SDL2Module : public Module
	{
		public:
			using Dependencies = TypeList<class PlatformModule>;

			SDL2Module();

			static inline bool IsInit() noexcept { return s_instance != nullptr; }
			static SDL2Module& Get();

			~SDL2Module() override;

		private:
			static SDL2Module* s_instance;
	};
}

#endif
