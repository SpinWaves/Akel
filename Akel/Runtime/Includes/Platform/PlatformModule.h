// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 09/02/2024

#ifndef __AK_PLATFORM_MODULE__
#define __AK_PLATFORM_MODULE__

#include <Platform/PreCompiled.h>
#include <Core/Module.h>
#include <Utils/TypeList.h>

#if (defined(AK_USE_SDL2) + defined(AK_USE_GLFW)) == 0
	#error "No backend enabled for the system interface (SDL2, GLFW, ...)"
#elif (defined(AK_USE_SDL2) + defined(AK_USE_GLFW)) != 1
	#error "Too much backends enabled for the system interface (SDL2, GLFW, ...)"
#endif

#if defined(AK_USE_SDL2)
	#include <Drivers/SDL2/SDL2Module.h>
#elif defined(AK_USE_GLFW)
	#include <Drivers/GLFW/GLFWModule.h>
#endif

namespace Ak
{
	class AK_PLATFORM_API PlatformModule : public Module
	{
		public:
			#if defined(AK_USE_SDL2)
				using Dependencies = TypeList<class CoreModule, SDL2Module>;
			#elif defined(AK_USE_GLFW)
				using Dependencies = TypeList<class CoreModule, GLFWModule>;
			#else
				using Dependencies = TypeList<class CoreModule>;
			#endif

			PlatformModule();

			static inline bool IsInit() noexcept { return s_instance != nullptr; }
			static PlatformModule& Get();

			~PlatformModule() override;

		private:
			static PlatformModule* s_instance;
	};
}

#endif
