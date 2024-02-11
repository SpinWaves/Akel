// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/02/2024
// Updated : 11/02/2024

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
