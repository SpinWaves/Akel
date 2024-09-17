// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_WEBGPU_INSTANCE__
#define __AK_WEBGPU_INSTANCE__

#include <Drivers/WebGPU/PreCompiled.h>

namespace Ak
{
	class AK_WEBGPU_API WebGPUInstance
	{
		public:
			WebGPUInstance();

			inline bool IsInit() const noexcept { return m_instance != nullptr; }
			inline WGPUInstance Get() const noexcept { return m_instance; }
			inline WGPUInstance operator()() const noexcept { return m_instance; }

			~WebGPUInstance();

		private:
			WGPUInstance m_instance = nullptr;
	};
}

#endif
