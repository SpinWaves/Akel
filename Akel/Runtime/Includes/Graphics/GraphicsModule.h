// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 11/03/2024

#ifndef __AK_GRAPHICS_MODULE__
#define __AK_GRAPHICS_MODULE__

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

			~GraphicsModule() override;

		private:
			void LoadDriver();
			int ScoreDriver(RendererDrivers driver);

		private:
			static GraphicsModule* s_instance;
			RHIRenderer* m_renderer = nullptr;
	};
}

#endif
