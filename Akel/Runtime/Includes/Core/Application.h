// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 06/02/2024

#ifndef __AK_CORE_APPLICATION__
#define __AK_CORE_APPLICATION__

#include <Core/PreCompiled.h>
#include <Utils/TypeList.h>

namespace Ak
{
	class AK_CORE_API Application
	{
		public:
			Application() = default;

			template<typename T>
			void LoadEngineModule();

			void ShutdownAllEngineModules();

			~Application() = default;

		private:
			std::vector<class Module*> m_modules;
	};
}

#include <Core/Application.inl>

#endif

