// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RHI_RENDER_PASS_H
#define AK_RHI_RENDER_PASS_H

#include <Graphics/PreCompiled.h>

namespace Ak
{
	class AK_GRAPHICS_API RHIRenderPass
	{
		public:
			RHIRenderPass() = default;

			virtual void Draw(std::uint32_t vertex_count, std::uint32_t instance_count = 1, std::uint32_t first_vertex = 0, std::uint32_t first_instance = 0) = 0;
			virtual void DrawIndexed(std::uint32_t index_count, std::uint32_t instance_count = 1, std::uint32_t first_index = 0, std::uint32_t vertex_offset = 0, std::uint32_t first_instance = 0) = 0;

			virtual ~RHIRenderPass() = default;
	};
}

#endif
