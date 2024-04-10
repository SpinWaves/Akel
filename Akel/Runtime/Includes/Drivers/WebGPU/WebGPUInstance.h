// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2024
// Updated : 10/04/2024

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
