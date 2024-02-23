// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/02/2024
// Updated : 23/02/2024

#ifndef __AK_RHI_DEFS__
#define __AK_RHI_DEFS__

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
}

#endif
