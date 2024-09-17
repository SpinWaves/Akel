// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_GRAPHICS_MODULE__
#define __AK_GRAPHICS_MODULE__

#include <Core/OS/LibLoader.h>
#include <Graphics/RHI/RHIRenderer.h>
#include <Graphics/PreCompiled.h>
#include <Core/Module.h>
#include <Utils/TypeList.h>
#include <Graphics/Enums.h>

namespace Ak
{
	class AK_GRAPHICS_API GraphicsModule : public Module
	{
		public:
			using Dependencies = TypeList<>;

			GraphicsModule();

			static inline bool IsInit() noexcept { return s_instance != nullptr; }
			static GraphicsModule& Get();

			inline RHIRenderer& GetRenderer() noexcept { return *m_renderer; }
			inline RendererDrivers GetChosenRendererDrivers() const noexcept { return m_chosen_driver; }

			~GraphicsModule() override;

		private:
			void LoadDriver();
			int ScoreDriver(RendererDrivers driver);

		private:
			static GraphicsModule* s_instance;
			RHIRenderer* m_renderer = nullptr;
			RendererDrivers m_chosen_driver = RendererDrivers::None;
			LibModule m_driver_lib = NullModule;
	};
}

#endif
