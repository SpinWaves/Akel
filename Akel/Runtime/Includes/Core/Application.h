// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 11/02/2024

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

			void Run();

			template<typename T>
			void LoadEngineModule();
			void ShutdownAllEngineModules();

			static Application& Get();
			static inline bool IsInit() noexcept { return s_instance != nullptr; }

			AK_FORCEINLINE constexpr void Quit() noexcept;

			~Application();

		private:
			static Application* s_instance;
			std::vector<Module*> m_modules;
			bool m_running = false;
	};
}

#include <Core/Application.inl>

#endif

