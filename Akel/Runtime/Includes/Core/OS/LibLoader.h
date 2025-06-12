// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_OS_LIB_LOADER_H
#define AK_CORE_OS_LIB_LOADER_H

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
