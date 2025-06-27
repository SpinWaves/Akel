// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RHI_DEFS_H
#define AK_RHI_DEFS_H

#include <Maths/Vec4.h>
#include <Utils/NonOwningPtr.h>
#include <Graphics/PreCompiled.h>
#include <Graphics/RHI/Enums.h>

namespace Ak
{
	struct AdapterMinimalSpecs
	{
		AdapterType type = AdapterType::Any;
		AdapterVendors vendors = AdapterVendorAny;
		std::size_t memory = 128; // Mo
	};

	using DeviceSize = std::uint64_t;

	constexpr std::size_t MAX_RENDER_TARGETS = 8;

	struct BufferDescription
	{
		const void* initial_data = nullptr;
		const char* debug_name = nullptr;
		DeviceSize size;
		BufferUsage usage;
		BufferType type;
	};

	struct TextureDescription
	{
		const void* initial_data = nullptr;
		const char* debug_name = nullptr;
		TextureFormat format;
		TextureType type;
		std::size_t width;
		std::size_t height;
		TextureFlags flags;
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
