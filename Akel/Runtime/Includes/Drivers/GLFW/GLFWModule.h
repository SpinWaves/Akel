// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_DRIVERS_GLFW_SI__
#define __AK_DRIVERS_GLFW_SI__

#include <Drivers/GLFW/PreCompiled.h>
#include <Core/Module.h>
#include <Utils/TypeList.h>

namespace Ak
{
	class AK_GLFW_API GLFWModule : public Module
	{
		public:
			using Dependencies = TypeList<>;

			GLFWModule();

			static inline bool IsInit() noexcept { return s_instance != nullptr; }
			static GLFWModule& Get();

			~GLFWModule() override;

		private:
			static GLFWModule* s_instance;
	};
}

#endif
