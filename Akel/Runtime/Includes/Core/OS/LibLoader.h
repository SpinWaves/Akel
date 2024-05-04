// This file is a part of Akel
// Authors : @maldavid
// Created : 12/02/2024
// Updated : 04/05/2024

#ifndef __AK_CORE_OS_LIB_LOADER__
#define __AK_CORE_OS_LIB_LOADER__

#include <Core/PreCompiled.h>
#include <Utils/NonCopyable.h>

namespace Ak
{
	using LibFunc = void (*)(void);
	using LibModule = void*;
	constexpr LibModule NullModule = nullptr;

	class AK_CORE_API LibLoader : public NonCopyable
	{
		public:
			LibLoader() = default;

			virtual LibFunc GetSymbol(LibModule module, const char* symbol) const = 0;

			virtual LibModule Load(const std::filesystem::path& path) = 0;
			virtual void UnloadLib(LibModule module) = 0;

			~LibLoader() = default;
	};
}

#endif
