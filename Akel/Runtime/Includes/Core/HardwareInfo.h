// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_HARDWARE_INFOS_H
#define AK_CORE_HARDWARE_INFOS_H

#include <Core/PreCompiled.h>
#include <Utils/NonCopyable.h>
#include <Utils/NonMovable.h>

#include <Core/Enums.h>

namespace Ak
{
	class AK_CORE_API HarwareInfos : public NonCopyable, NonMovable
	{
		public:
			HarwareInfos();

			inline const char* GetCpuBrandString() const;
			inline unsigned int GetCpuThreadCount() const;
			inline ProcVendor GetCpuVendor() const;
			std::string_view GetCpuVendorName() const;
			inline std::uint64_t GetSystemTotalMemory() const;

			inline bool HasCapability(ProcCaps capability) const;

			static void Cpuid(std::uint32_t functionId, std::uint32_t subFunctionId, std::uint32_t result[4]);
			static bool IsCpuidSupported();

			~HarwareInfos() = default;

		private:
	};
}

#endif
