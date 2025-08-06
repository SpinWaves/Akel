// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RHI_DEFS_H
#define AK_RHI_DEFS_H

#include <Maths/Vec4.h>
#include <Utils/NonOwningPtr.h>
#include <Graphics/PreCompiled.h>
#include <Graphics/RHI/Enums.h>
#include <Maths/Vec2.h>

namespace Ak
{
	struct AdapterMinimalSpecs
	{
		AdapterType type = AdapterType::Any;
		AdapterVendors vendors = AdapterVendorAny;
		std::size_t memory = 128; // MB
	};

	using DeviceSize = std::uint64_t;

	constexpr std::size_t MAX_RENDER_TARGETS = 8;

	struct BufferDescription
	{
		DeviceSize size;
		BufferUsage usage;
		BufferType type;
	};

	struct TextureDescription
	{
		TextureDimension dimension;
		TextureFormat format;
		TextureUsage usage;
		Vec2ui size;
		std::uint32_t depth;
		std::uint8_t level_count;
	};

	struct GraphicPipelineDescription
	{
		std::array<NonOwningPtr<class RHITexture>, MAX_RENDER_TARGETS> render_targets;
		NonOwningPtr<class RHIShader> vertex_shader;
		NonOwningPtr<class RHIShader> fragment_shader;
		Vec4f clear_color;
		std::string_view debug_name;
		NonOwningPtr<class RHITexture> depth_target;
		CullMode cull_mode = CullMode::Back;
		RenderMode render_mode = RenderMode::Fill;
		std::size_t line_width = 1;
		bool clear_targets = false;
	};

	struct ShaderDescription
	{
	};
	
	struct RenderPassDescription
	{
	};

	struct FrameBufferDescription
	{
	};
}

#endif
