// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

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
	constexpr std::size_t ProcCapsCount = static_cast<std::size_t>(ProcCaps::EndEnum);

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

	enum class LogType
	{
		Debug = 0,
		Message,
		Warning,
		Error,
		FatalError,

		EndEnum
	};
	constexpr std::size_t LogTypeCount = static_cast<std::size_t>(LogType::EndEnum);

	enum FileModeBits
	{
		FileModeNone = 0,
		FileModeOverride = 1 << 0,
		FileModeAppend = 1 << 1,
		FileModeBinary = 1 << 2,
	};
	using FileMode = int;
	constexpr std::size_t FileModeCount = 4;
}

#endif
