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
	using DeviceSize = std::uint64_t;

	constexpr std::size_t MacRenderTargets = 8;

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
		std::vector<NonOwningPtr<class RHIShader>> shaders;
		std::array<NonOwningPtr<class RHITexture>, MacRenderTargets> render_targets;
		Vec4f clear_color;
		const char* debug_name = nullptr;
		NonOwningPtr<class RHITexture> depth_target;
		CullMode cull_mode = CullMode::Back;
		RenderMode render_mode = RenderMode::Fill;
		std::size_t line_width = 1;
		bool clear_target = false;
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

	struct PhysicalDeviceMinimalSpecs
	{
		PhysicalDeviceType type = PhysicalDeviceType::Any;
		PhysicalDeviceVendors vendors = PhysicalDeviceVendorAny;
		std::size_t memory = 128; // Mo
	};
}

#endif
