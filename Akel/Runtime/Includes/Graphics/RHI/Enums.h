// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RHI_ENUMS_H
#define AK_RHI_ENUMS_H

#include <Graphics/PreCompiled.h>

#ifdef None // Thanks x11 :)
	#undef None
#endif

namespace Ak
{
	enum class AdapterType
	{
		Any = 0,
		Other,
		CPU,
		Virtual,
		Integrated,
		Discrete,

		EndEnum
	};
	constexpr std::size_t AdapterTypeCount = static_cast<std::size_t>(AdapterType::EndEnum);

	enum AdapterVendorBits
	{
		AdapterVendorAny = 1 << 0,
		AdapterVendorAmd = 1 << 1,
		AdapterVendorMesa = 1 << 2,
		AdapterVendorImgTec = 1 << 3,
		AdapterVendorNvidia = 1 << 4,
		AdapterVendorArm = 1 << 5,
		AdapterVendorBroadcom = 1 << 6,
		AdapterVendorQualcomm = 1 << 7,
		AdapterVendorIntel = 1 << 8,
		AdapterVendorSamsungAMD = 1 << 9,
		AdapterVendorMicrosoft = 1 << 10,
	};
	constexpr std::size_t AdapterVendorsCount = 11;
	using AdapterVendors = std::uint32_t;

	enum class BufferType
	{
		Constant = 0,
		HighDynamic, // typically stored in RAM
		LowDynamic,  // typically stored in VRAM

		EndEnum
	};
	constexpr std::size_t BufferTypeCount = static_cast<std::size_t>(BufferType::EndEnum);

	enum BufferUsageBits
	{
		BufferUsageTransferSrc = 1 << 0,
		BufferUsageTransferDst = 1 << 1,
		BufferUsageVertex = 1 << 2,
		BufferUsageIndex = 1 << 3,
		BufferUsageUniform = 1 << 4,
		BufferUsageStorage = 1 << 5
	};
	constexpr std::size_t BufferUsageCount = 6;
	using BufferUsage = std::uint32_t;

	enum class CullMode
	{
		None = 0,
		Front,
		Back,
		BackAndFront,

		EndEnum
	};
	constexpr std::size_t CullModeCount = static_cast<std::size_t>(CullMode::EndEnum);

	enum class RenderMode
	{
		Fill = 0,
		Wireframe,
		Points,

		EndEnum
	};
	constexpr std::size_t RenderModeCount = static_cast<std::size_t>(RenderMode::EndEnum);

	enum class TextureFormat
	{
		None = 0,
		R8_Unorm,
		R8G8_Unorm,
		R8G8B8_Unorm,
		R8G8B8A8_Unorm,

		R8_UInt,

		R11G11B10_Float,
		R10G10B10A2_Unorm,

		R32_Int,
		R32G32_Int,
		R32G32B32_Int,
		R32G32B32A32_Int,

		R32_UInt,
		R32G32_UInt,
		R32G32B32_UInt,
		R32G32B32A32_UInt,

		R16_Float,
		R16G16_Float,
		R16G16B16_Float,
		R16G16B16A16_Float,

		R32_Float,
		R32G32_Float,
		R32G32B32_Float,
		R32G32B32A32_Float,

		D16_Unorm,
		D32_Float,
		D16_Unorm_S8_UInt,
		D24_Unorm_S8_UInt,
		D32_Float_S8_UInt,

		EndEnum
	};
	constexpr std::size_t TextureFormatCount = static_cast<std::size_t>(TextureFormat::EndEnum);

	enum class TextureType
	{
		Color = 0,
		Depth,
		DepthArray,
		Cube,
		Other,

		EndEnum
	};
	constexpr std::size_t TextureTypeCount = static_cast<std::size_t>(TextureType::EndEnum);

	enum TextureFlagsBits
	{
		TextureFlagSampled = 1 << 0,
		TextureFlagStorage = 1 << 1,
		TextureFlagDepthStencil = 1 << 2,
	};
	constexpr std::size_t TextureFlagsCount = 3;
	using TextureFlags = std::uint32_t;
}

#endif
