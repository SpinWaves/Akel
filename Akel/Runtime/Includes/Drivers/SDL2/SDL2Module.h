// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_DRIVERS_SDL2_MODULE_H
#define AK_DRIVERS_SDL2_MODULE_H

#include <Drivers/SDL2/PreCompiled.h>
#include <Core/Module.h>
#include <Utils/TypeList.h>

namespace Ak
{
	class AK_SDL2_API SDL2Module : public Module
	{
		public:
			using Dependencies = TypeList<>;

			SDL2Module();

			static inline bool IsInit() noexcept { return s_instance != nullptr; }
			static SDL2Module& Get();

			static std::string GetEngineModuleVersion();

			~SDL2Module() override;

		private:
			static SDL2Module* s_instance;
	};
}

#endif
