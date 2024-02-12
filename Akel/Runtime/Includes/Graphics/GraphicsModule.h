// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 12/02/2024

#ifndef __AK_GRAPHICS_MODULE__
#define __AK_GRAPHICS_MODULE__

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

			GraphicsModule(RenderBackend backend);

			static inline bool IsInit() noexcept { return s_instance != nullptr; }
			static GraphicsModule& Get();

			~GraphicsModule() override;

		private:
			static GraphicsModule* s_instance;
	};
}

#endif
