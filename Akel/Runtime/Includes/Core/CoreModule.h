// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_COREMODULE_H
#define AK_CORE_COREMODULE_H

#include <Core/PreCompiled.h>
#include <Core/Module.h>
#include <Core/Ticks.h>
#include <Utils/TypeList.h>
#include <Core/ConfigurationFile.h>
#include <Core/VirtualFileSystem.h>

namespace Ak
{
	class AK_CORE_API CoreModule : public Module
	{
		public:
			using Dependencies = TypeList<>;

			CoreModule();

			static inline bool IsInit() noexcept { return s_instance != nullptr; }
			static CoreModule& Get();

			inline Ticks& GetTicksReference() { return m_ticks; }
			inline VirtualFileSystem& GetVirtualFileSystem() { return m_filesystem; }

			static std::string GetEngineModuleVersion();

			~CoreModule() override;

		private:
			static CoreModule* s_instance;
			Ticks m_ticks;
			VirtualFileSystem m_filesystem;
			//ConfigurationFile m_engine_config_file;
	};

	AK_FORCEINLINE VirtualFileSystem& GetVFS() { return CoreModule::Get().GetVirtualFileSystem(); }
}

#endif
