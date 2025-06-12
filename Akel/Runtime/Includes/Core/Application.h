// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_APPLICATION_H
#define AK_CORE_APPLICATION_H

#include <Core/PreCompiled.h>
#include <Utils/TypeList.h>
#include <Core/ComponentStack.h>
#include <Core/EngineConfig.h>
#include <Core/Module.h>

namespace Ak
{
	class AK_CORE_API Application : public ComponentStack
	{
		public:
			Application(const EngineConfig& config);

			void Run();

			template<typename T, typename...Args>
			void LoadEngineModule(Args&&... args);
			void ShutdownAllEngineModules();

			static inline bool IsInit() noexcept { return s_instance != nullptr; }
			static Application& Get();

			inline const EngineConfig& GetEngineConfig() const noexcept { return m_engine_config; }
			AK_FORCEINLINE std::string_view GetEngineVersion() const { return m_engine_version; }

			AK_FORCEINLINE constexpr void Quit() noexcept;

			~Application();

		private:
			static Application* s_instance;
			EngineConfig m_engine_config;
			std::string m_engine_version;
			std::vector<Module*> m_modules;
			bool m_running = false;
	};
}

#include <Core/Application.inl>

#endif

