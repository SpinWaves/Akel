// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_PLATFORM_MODULE__
#define __AK_PLATFORM_MODULE__

#include <Platform/SI/Window.h>
#include <Platform/SI/Input.h>
#include <Platform/PreCompiled.h>
#include <Core/Module.h>
#include <Utils/TypeList.h>

namespace Ak
{
	class AK_PLATFORM_API PlatformModule : public Module
	{
		public:
			using Dependencies = TypeList<class CoreModule>;

			PlatformModule();

			static inline bool IsInit() noexcept { return s_instance != nullptr; }
			static PlatformModule& Get();

			void Update() override;

			UniquePtr<SIWindow> CreateDummyWindow();

			inline Inputs& GetInputs() noexcept { return *m_backend_inputs; }

			~PlatformModule() override;

		private:
			static PlatformModule* s_instance;
			Inputs* m_backend_inputs = nullptr;
	};
}

#endif
