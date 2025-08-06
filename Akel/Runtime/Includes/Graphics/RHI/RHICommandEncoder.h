// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RHI_COMMAND_ENCODER_H
#define AK_RHI_COMMAND_ENCODER_H

#include <Graphics/PreCompiled.h>
#include <Graphics/RHI/RHICommandBuffer.h>

namespace Ak
{
	class AK_GRAPHICS_API RHICommandEncoder
	{
		public:
			RHICommandEncoder(class RHIDevice& device) : m_device(device) {}

			virtual UniquePtr<class RHIRenderPass> BeginRenderPass() = 0;

			virtual ~RHICommandEncoder() = default;

		private:
			class RHIDevice& m_device;
	};
}

#endif
