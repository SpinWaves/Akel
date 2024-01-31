// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 31/01/2024

#ifndef __AK_CORE_HARDWARE_INFOS__
#define __AK_CORE_HARDWARE_INFOS__

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
