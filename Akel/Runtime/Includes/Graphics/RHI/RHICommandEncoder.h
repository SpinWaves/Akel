// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RHI_COMMAND_ENCODER_H
#define AK_RHI_COMMAND_ENCODER_H

#include <Graphics/PreCompiled.h>
#include <Graphics/RHI/RHICommandBuffer.h>

namespace Ak
{
	#define AK_RHI_FOREACH_COMMANDS(command) \
		command(BeginComputePass) \
		command(BeginRenderPass) \
		command(BindComputePipeline) \
		command(BindComputeShaderBinding) \
		command(BindIndexBuffer) \
		command(BindRenderPipeline) \
		command(BindRenderShaderBinding) \
		command(BindVertexBuffer) \
		command(BlitImage) \
		command(BlitImageToSwapchain) \
		command(BuildMipmaps) \
		command(CopyBuffer) \
		command(CopyImage) \
		command(Draw) \
		command(DrawIndexed) \
		command(Dispatch) \
		command(EndComputePass) \
		command(EndRenderPass) \
		command(ImageBarrier) \
		command(MemoryBarrier) \
		command(NextSubpass) \
		command(PushConstants) \
		command(SetScissor) \
		command(SetViewport) \

	class AK_GRAPHICS_API RHICommandEncoder
	{
		public:
			RHICommandEncoder() = default;

			virtual void Draw(std::uint32_t vertex_count, std::uint32_t instance_count = 1, std::uint32_t first_vertex = 0, std::uint32_t first_instance = 0) = 0;
			virtual void DrawIndexed(std::uint32_t index_count, std::uint32_t instance_count = 1, std::uint32_t first_index = 0, std::uint32_t vertex_offset = 0, std::uint32_t first_instance = 0) = 0;

			virtual ~RHICommandEncoder() = default;
	};
}

#endif
