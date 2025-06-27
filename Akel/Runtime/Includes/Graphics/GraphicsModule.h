// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_GRAPHICS_MODULE_H
#define AK_GRAPHICS_MODULE_H

#include <Core/OS/LibLoader.h>
#include <Graphics/PreCompiled.h>
#include <Core/Module.h>
#include <Utils/TypeList.h>
#include <Graphics/Enums.h>
#include <Graphics/Renderer/RenderCore.h>

namespace Ak
{
	class AK_GRAPHICS_API GraphicsModule : public Module
	{
		public:
			using Dependencies = TypeList<class CoreModule, class PlatformModule>;

			GraphicsModule();

			static inline bool IsInit() noexcept { return s_instance != nullptr; }
			static GraphicsModule& Get();

			inline RenderCore& GetRenderCore() noexcept { return *p_renderer; }
			inline RendererDrivers GetChosenRendererDrivers() const noexcept { return m_chosen_driver; }

			static std::string GetEngineModuleVersion();

			~GraphicsModule() override;

		private:
			void LoadDriver();
			int ScoreDriver(RendererDrivers driver);

		private:
			static GraphicsModule* s_instance;
			UniquePtr<RenderCore> p_renderer;
			RendererDrivers m_chosen_driver = RendererDrivers::None;
			LibModule m_driver_lib = NullModule;
	};
}

#endif
