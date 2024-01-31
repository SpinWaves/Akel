// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 31/01/2024

#ifndef __AK_CORE_ENUMS__
#define __AK_CORE_ENUMS__

#include <Core/PreCompiled.h>

namespace Ak
{
	enum class ProcCaps
	{
		x64 = 0,
		AES,
		AVX,
		FMA3,
		FMA4,
		MMX,
		Popcnt,
		RDRAND,
		XOP,
		SSE,
		SSE2,
		SSE3,
		SSSE3,
		SSE41,
		SSE42,
		SSE4a,

		EndEnum
	};
	constexpr std::size_t ProcCapsCount = static_cast<std::size_t>(ProcCaps::EndEnum) + 1;

	enum class ProcVendor
	{
		Unknown = -1,

		ACRN,
		AMD,
		Ao486,
		AppleRosetta2,
		Bhyve,
		Centaur,
		Cyrix,
		Elbrus,
		Hygon,
		HyperV,
		Intel,
		KVM,
		MicrosoftXTA,
		NSC,
		NexGen,
		Parallels,
		QEMU,
		QNX,
		Rise,
		SIS,
		Transmeta,
		UMC,
		VIA,
		VMware,
		Vortex,
		XenHVM,
		Zhaoxin,

		EndEnum
	};
	constexpr std::size_t ProcVendorCount = static_cast<std::size_t>(ProcVendor::EndEnum) + 1;
}

#endif
