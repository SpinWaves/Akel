// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_VULKAN_ENUMS__
#define __AK_VULKAN_ENUMS__

#include <Drivers/Vulkan/PreCompiled.h>

namespace Ak
{
	enum class VulkanPhysicalDeviceVendorID : std::uint32_t
	{
		Unknown = 0,
		Amd = 0x1002,
		ImgTec = 0x1010,
		Nvidia = 0x10DE, 
		Arm = 0x13B5, 
		Broadcom = 0x14E4,
		Qualcomm = 0x5143,
		Intel = 0x8086,
		Apple = 0x106B,
		Vivante = 0x7a05,
		VeriSilicon = 0x1EB1,
		SamsungAMD = 0x144D,
		Microsoft = 0x1414,
		Kazan = 0x10003,
		Codeplay = 0x10004,
		Mesa = 0x10005,
	};
	constexpr std::size_t VulkanPhysicalDeviceVendorIDCount = 16;
}

#endif
