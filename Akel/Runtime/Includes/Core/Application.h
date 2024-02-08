// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 08/02/2024

#ifndef __AK_CORE_APPLICATION__
#define __AK_CORE_APPLICATION__

#include <Core/PreCompiled.h>
#include <Utils/TypeList.h>
#include <Core/ComponentStack.h>
#include <Core/Module.h>

namespace Ak
{
	class AK_CORE_API Application : public ComponentStack
	{
		public:
			Application();

			template<typename T>
			void LoadEngineModule();

			void ShutdownAllEngineModules();

			~Application() = default;

		private:
			std::vector<Module*> m_modules;
	};
}

#include <Core/Application.inl>

#endif

